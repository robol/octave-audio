%SNDREAD Reads the signals from a sound file. 
%
% -- Mex File: [SIGNAL, FREQUENCY] = sndread (FILENAME)
%
%     This function reads the data contained in the
%     input file FILENAME. 
%
%     The output SIGNAL is a matrix of size c x n 
%     where c is the number of channels of FILENAME 
%     and n is the number f samples. 
%
%     The value FREQUENCY is the sample rate of the
%     original file. It needs to be passed to the
%     function SNDWRITE in order to encode an output
%     file correctly. 
