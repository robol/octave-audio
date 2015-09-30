# Octave Sound 
Octave-Sound is a simple package for Octave
(that should also be compatible
with MATLAB) that allows to read, play and 
write sound files from Octave. 

It was originally written to allow to easily
read and write multichannel audio from/to WAV
files. 

## Quick guide

If you have Octave audio installed you can use it
in the following way: 
```
 % This call returns a c x n matrix where c is the number
 % of audio channels and n the number of samples. 
 % frequency is the frequency of the original audio
 % file. 
 >> [data, frequency] = sndread ('test.wav');

 % Listen to the signal. 
 >> sndplay (data, frequency);

 % We apply some filter on every channel.
 >> filtered_signal = zeros (size(data));
 >> for i = 1 : size(data, 1)
  ... filtered_signal(i,:) = conv (data(i,:), my_filter, 'same');
 end
 
 % We write back the file to a WAV file. 
 >> sndwrite ('filtered_test.wav', filtered_signal, frequency);
```

## How to obtain it

You can download it from Github, and compiling by
simply typing make in the source directory. 

If you want to compile it for MATLAB you will need
to adjust the Makefile. Open it with your preferred
text editor and follow the instructions. 

Notice that in order to compile it you need libsndfile
and PulseAudio. The former should be available on most
systems, while the latter only work on POSIX systems
and is usually installed by default only on GNU/Linux. 

On Ubuntu, you can obtain all the dependencies by typing
```
$ sudo apt-get install libsndfile1-dev libpulse-dev
```



