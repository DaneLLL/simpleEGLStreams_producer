(verified on r24.2.1)

1 Environment setup
(install CUDA toolkit via jetpack)
$ sudo apt-get install libegl1-mesa-dev
$ sudo apt-get install libgles2-mesa-dev

2 Push the sample amd make
$ cd simpleEGLStreams_producer
$ make

3 Overwrite libnveglstreamproducer.so 
sudo cp -i libnveglstreamproducer.so /usr/lib/aarch64-linux-gnu/tegra

4 Run 
$ nvgstcapture-1.0 --camsrc=3 --prev-res=3

Reference samples
~/NVIDIA_CUDA-8.0_Samples/2_Graphics/simpleGLES_EGLOutput
~/NVIDIA_CUDA-8.0_Samples/3_Imaging/EGLStreams_CUDA_Interop
