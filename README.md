# MSc-EEG-Hardware

I tried downsampling the raw data to 100 Hz and the Epochlength now is 3000. However, it still exceeds the RAM. I think this is because when calculating spectral power in frequency bands, we need to do multiply the window and the length of its coefficients is too large. And when doing calculation in the frequency domain,(see "freq_domain.c","computeperiodogram.c","bandpower.c")

Will it be possible to reduce the Epochlength without doing downsampling and retrained the model?
