# Octave Sound 
Octave-Sound is a simple package for Octave
(that should also be compatible
with MATLAB) that allows to read, play and 
write sound files from Octave. 

It was originally written to allow to easily
read and write multichannel audio from/to WAV
files. 

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



