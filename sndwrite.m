%SNDWRITE Write an audio signal to a file. 
%
% -- Mex File: sndwrite (FILENAME, DATA)
% -- Mex File: sndwrite (FILENAME, DATA, FREQUENCY)
% -- Mex File: sndwrite (FILENAME, DATA, FREQUENCY, FORMAT)
%
%     Write the signal stored in the matrix DATA to the
%     the file named FILENAME. 
%
%     An optional number can be specified for the frequency
%     otherwise 48000 Hz is assumed. 
%
%     The parameter FORMAT can be used to specify the desired
%     output format as a string. The supported values are: 
%
%     - S16LE: Signed integer 16 bit little endian
%     - S16BE: Signed integer 16 bit big endian
%     - S16NE: Signed integer 16 bit native endian
%
