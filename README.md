# MSc-EEG-Hardware

I tried downsampling the raw data to 100 Hz and the Epochlength now is 3000. However, it still exceeds the RAM. When extracting the features, we creat many arraies with length of 3000 and causing stack overflow.

Will it be possible to reduce the Epochlength without doing downsampling and retrained the model?
