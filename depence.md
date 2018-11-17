## libzip
> https://github.com/nih-at/libzip

On Mac: NOTE use `-lzip`
```
make build && cd build
cmake -DBUILD_SHARED_LIBS=OFF -DENABLE_OPENSSL=OFF ..
make
```
or just 

```
brew install libzip
```


## SDS
> https://github.com/antirez/sds

On Mac: copy the source file into dep/sds