#include <mex.h>
#include <sndfile.h>

void mexFunction (int nlhs, mxArray * plhs[], 
		  int nrhs, const mxArray * prhs[])
{
  /* Reads a sound file and returns an array containing
   * the sample. The type of the samples will depend on 
   * the type of samples inside the file. */
  
  char * filename = NULL;
  mwSize filename_length = 0;
  int read_count;
  SF_INFO sf_info;
  
  if (nrhs < 1)
    {
      mexErrMsgTxt ("you need "
		     "to specify a valid filename");
    }

  if (nrhs > 1)
    {
      mexErrMsgTxt ("Please specify 1 argument only");
    }
  
  if (! mxIsChar (prhs[0]))
    {
      mexErrMsgTxt ("The first parameter must be a string");
    }

  filename_length = 1 + mxGetN (prhs[0]);
  filename = malloc (sizeof (char) * filename_length);
  read_count = mxGetString (prhs[0], filename, filename_length);

  SNDFILE * sf = sf_open (filename, SFM_READ, &sf_info);

  if (sf == NULL)
    {
      mexErrMsgTxt ("Error opening the input file");      
    }

  plhs[0] = mxCreateDoubleMatrix (sf_info.channels, 
				  sf_info.frames, 
				  mxREAL);

  /* Notice that since Octave stores the arrays by columns in this way
   * we get that every row of the output is a channel. */
  sf_read_double (sf, mxGetPr (plhs[0]), sf_info.frames*
		  sf_info.channels);

  /* If the user requests it, we set the samplerate as second
   * output. */
  if (nlhs > 1)
    {
      plhs[1] = mxCreateDoubleScalar (sf_info.samplerate);
    }

  sf_close (sf);
  free (filename);
}
