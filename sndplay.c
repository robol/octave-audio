#include "mex.h"
#include <pulse/simple.h>

void mexFunction (int nlhs, mxArray * plhs[],
		  int nrhs, const mxArray* prhs[])
{
  pa_sample_spec ss = {
    .format = PA_SAMPLE_S16NE,
    .rate   = 48000,
    .channels = 2
  };

  if (nrhs > 1)
    {
      ss.rate = *mxGetPr (prhs[1]);
    }

  pa_simple * s = NULL;
  int error, i;

  s = pa_simple_new (NULL, "Octave", PA_STREAM_PLAYBACK, NULL, 
		     "playback", &ss, NULL, NULL, &error);
  if (! s) {
    mexErrMsgTxt ("SNDPLAY: Failed to initialize the audio subsytem");
  }

  size_t size = (size_t) mxGetN(prhs[0]) * mxGetM(prhs[0]);
  short *  data = malloc (sizeof (short) * size);
  double * ddata = mxGetPr (prhs[0]);

  for (i = 0; i < size; i++)
    {
      data[i] = (short) (32768 * ddata[i]);
    }

  pa_simple_write (s, data, size * sizeof (short) , &error);
  pa_simple_free (s);
  free (data);
}
