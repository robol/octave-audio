MEX = mkoctfile --mex
MEXEXT=.mex

# Use the following if you want to compile the package
# for MATLAB. Notice that C99 is required in order
# to be able to compile against the Pulse headers. 
#
# Notice that in this case you also need to adjust the
# extension to the one used on your architecture. 
#
# MEX = mex CFLAGS="\$$CFLAGS -std=c99"
# MEXEXT = .mexa64

MEX_FILES = \
	sndplay$(MEXEXT) \
	sndread$(MEXEXT) \
	sndwrite$(MEXEXT)

M_FILES = \
	sndplay.m \
	sndplot.m \
	sndread.m \
	sndwrite.m 

all: $(MEX_FILES) octave-sound.tar.gz

octave-sound.tar.gz: $(MEX_FILES)
	rm -rf octave-sound
	mkdir octave-sound
	cp $(MEX_FILES) $(M_FILES) octave-sound
	[ -r libsndfile.so ] && cp libsndfile.so octave-sound/
	tar czf octave-sound.tar.gz octave-sound/

%$(MEXEXT): %.c
	$(MEX) $< -L. -lsndfile -lpulse-simple -Wl,-R.

clean:
	rm -rf $(MEX_FILES) *.o octave-sound.tar.gz octave-sound/
