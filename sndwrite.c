#include <mex.h>
#include <sndfile.h>
#include <string.h>

void mexFunction (int nlhs, mxArray * plhs[], 
		  int nrhs, const mxArray * prhs[])
{
  /* Reads a sound file and returns an array containing
   * the sample. The type of the samples will depend on 
   * the type of samples inside the file. */  
  char * filename = NULL;
  mwSize filename_length = 0;
  int read_count;

  /* Here are a reasonable set of default values, 
   * in case the user hasn't specified anything. */
  SF_INFO sf_info = {
    .samplerate = 48000,
    .format = SF_FORMAT_WAV | SF_FORMAT_PCM_16 | SF_ENDIAN_CPU,
    .sections = 1,
    .seekable = 1
  };
  
  if (nrhs < 1)
    {
      mexErrMsgTxt ("You need to specify a "
		    "valid filename");
    }

  if (nrhs < 2 || ! mxIsDouble (prhs[1]))
    {
      mexErrMsgTxt ("You need to specify a floating point matrix"
		    " with the samples");
    }

  if (nrhs >= 3)
    {
      sf_info.samplerate = *mxGetPr (prhs[2]);
    }

  if (nrhs >= 4)
    {
      char format[255];

      if (! mxIsChar (prhs[3]))
	mexErrMsgTxt ("The third parameter should be string");

      mxGetString (prhs[3], format, 255);
      
      if (strcmp (format, "S16LE") == 0) 
	sf_info.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16 | SF_ENDIAN_LITTLE;
      else if (strcmp (format, "S16NE") == 0)
	sf_info.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16 | SF_ENDIAN_CPU;
      else if (strcmp (format, "S16BE") == 0)
	sf_info.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16 | SF_ENDIAN_BIG;
      else {
	mexErrMsgTxt ("Unsupported format");
      }
    }

  if (nrhs > 5)
    mexErrMsgTxt ("Too many input arguments");

  if (! mxIsChar (prhs[0]))
    {
      mexErrMsgTxt ("The first parameter must be a string");
    }

  /* Fill in the struct. In particular, select the number of channels
   * in base of the dimensions of the input matrix. */
  sf_info.channels = mxGetM(prhs[1]);

  filename_length = 1 + mxGetN (prhs[0]);
  filename = malloc (sizeof (char) * filename_length);
  read_count = mxGetString (prhs[0], filename, filename_length);

  SNDFILE * sf = sf_open (filename, SFM_WRITE, &sf_info);

  /* Set the number of frames to be written. */
  sf_info.frames = mxGetN(prhs[1]);

  if (sf == NULL)
    {
      mexErrMsgTxt ("Error opening the output file");      
    }

  /* Notice that since Octave stores the arrays by columns in this way
   * we get that every row of the output is a channel. */
  sf_write_double (sf, mxGetPr (prhs[1]), sf_info.frames*
		   sf_info.channels);

  sf_close (sf);
  free (filename);
}
