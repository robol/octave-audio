MEXEXT=.mex

MEX_FILES = \
	sndplay$(MEXEXT) \
	sndread$(MEXEXT) \
	sndwrite$(MEXEXT)

M_FILES = \
	sndplay.m \
	sndplot.m \
	sndread.m \
	sndwrite.m 

MKOCTFILE = mkoctfile

all: $(MEX_FILES) octave-sound.tar.gz

octave-sound.tar.gz: $(MEX_FILES)
	rm -rf octave-sound
	mkdir octave-sound
	cp $(MEX_FILES) $(M_FILES) octave-sound
	[ -r libsndfile.so ] && cp libsndfile.so octave-sound/
	tar czf octave-sound.tar.gz octave-sound/

%$(MEXEXT): %.c
	$(MKOCTFILE) --mex $< -L. -lsndfile -lpulse-simple -Wl,-R.

clean:
	rm -rf $(MEX_FILES) *.o octave-sound.tar.gz octave-sound/
