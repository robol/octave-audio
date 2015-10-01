#include "mex.h"
#include <pulse/simple.h>

#ifdef MATLAB_MEX_FILE
extern bool utIsInterruptPending();
#endif

#define BUFFER_SIZE 1024

void mexFunction (int nlhs, mxArray * plhs[],
		  int nrhs, const mxArray* prhs[])
{
  /* These are the default values that are set whenever
   * the user does not make an explicit choice. */
  pa_sample_spec ss = {
    .format = PA_SAMPLE_S16NE,
    .rate   = 48000,
    .channels = 2
  };

  /* Here is the buffer that we use to play the data */
  short buffer[BUFFER_SIZE];  
  size_t size, cursor;

  int error, i;
  pa_simple * s = NULL;  

  if (nrhs > 1)
    ss.rate = *mxGetPr (prhs[1]);

  s = pa_simple_new (NULL, "Octave", PA_STREAM_PLAYBACK, NULL, 
		     "playback", &ss, NULL, NULL, &error);
  if (! s) {
    mexErrMsgTxt ("Failed to initialize the audio subsytem");
  }

  size = (int) mxGetN(prhs[0]) * mxGetM(prhs[0]);
  double * ddata = mxGetPr (prhs[0]);

  for (cursor = 0; cursor < size; cursor += BUFFER_SIZE) {
    for (i = 0; i < MIN (BUFFER_SIZE, size - cursor); i++) {
      buffer[i] = (short) (32767 * ddata[cursor + i]);
    }

    /* In case the user press CTRL+C while playing we stop
     * doing it and return. This is only supported in 
     * MATLAB, though. */
#ifdef MATLAB_MEX_FILE
    if (utIsInterruptPending ())
      goto cleanup;
#endif

    pa_simple_write (s, buffer, MIN (BUFFER_SIZE, size - cursor) * 
      sizeof (short), &error);
  }

  cleanup:
      pa_simple_free (s);
}
