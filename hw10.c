/*
 * HW10: GPU Computing
 * CSCI 5239 Spring 2016
 * Diana Southard
 *
 * Create a program that uses CUDA to speed up calculations. Compare
 * the speed of a CPU based implementation with a GPU implementation.
 *
 * Program Use: Calculate speedup of squaring calculations using CUDA
 *
 * Parameters: [-v] <Array Length: Recommend 10-100> <Block Size: Recommend 4>
 *  -v      		Verbose - show hardware details
 *  Block Size   	Block width (width squared <= max threads/block)
 *  Array Length  	Number of elements in arrays
 *
 * Simple CUDA programs have a basic flow:
 * 	1.The host initializes an array with data.
 * 	2.The array is copied from the host to the memory on the CUDA device.
 * 	3.The CUDA device operates on the data in the array.
 * 	4.The array is copied back to the host.
 *
 */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <cuda.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

/*
 *  Return elapsed wall time since last call (seconds)
 */
static double t0=0;
double Elapsed(void)
{
#ifdef _WIN32
	//  Windows version of wall time
	LARGE_INTEGER tv,freq;
	QueryPerformanceCounter((LARGE_INTEGER*)&tv);
	QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
	double t = tv.QuadPart/(double)freq.QuadPart;
#else
	//  Unix/Linux/OSX version of wall time
	struct timeval tv;
	gettimeofday(&tv,NULL);
	double t = tv.tv_sec+1e-6*tv.tv_usec;
#endif
	double s = t-t0;
	t0 = t;
	return s;
}

/*
 *  Print message to stderr and exit
 */
void Fatal(const char* format , ...)
{
	va_list args;
	va_start(args,format);
	vfprintf(stderr,format,args);
	va_end(args);
	exit(1);
}


/*
 *  Initialize fastest GPU device
 */
int InitGPU(int verbose)
{
	//  Get number of CUDA devices
	int num;
	if (cudaGetDeviceCount(&num)) Fatal("Cannot get number of CUDA devices\n");
	if (num<1) Fatal("No CUDA devices found\n");

	//  Get fastest device
	cudaDeviceProp prop;
	int   MaxDevice = -1;
	int   MaxGflops = -1;
	for (int dev=0;dev<num;dev++)
	{
		if (cudaGetDeviceProperties(&prop,dev)) Fatal("Error getting device %d properties\n",dev);
		int Gflops = prop.multiProcessorCount * prop.clockRate;
		if (verbose) printf("CUDA Device %d: %s Gflops %f Processors %d Threads/Block %d\n",dev,prop.name,1e-6*Gflops,prop.multiProcessorCount,prop.maxThreadsPerBlock);
		if(Gflops > MaxGflops)
		{
			MaxGflops = Gflops;
			MaxDevice = dev;
		}
	}

	//  Print and set device
	if (cudaGetDeviceProperties(&prop,MaxDevice)) Fatal("Error getting device %d properties\n",MaxDevice);
	printf("Fastest CUDA Device %d: %s\n",MaxDevice,prop.name);
	cudaSetDevice(MaxDevice);

	//  Return max thread count
	return prop.maxThreadsPerBlock;
}

/* Kernel that executes on the CUDA device
 * '__global__' indicates that  this is a kernel function that should be processed
 * by NVCC to create machine code that executes on the CUDA device, not the host
 * 			array[i] = array[i] * array[i]
 */
__global__ void squareDevice(float *array, int N)
{
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	if (idx<N) array[idx] *= array[idx];
}

/*
 *
 */
void squareHost(float *array, int N)
{
	for (int i = 0; i < N; i++)
	{
		array[i] *= array[i];
	}
}

// Main routine that executes on the host
int main(int argc, char* argv[])
{
	//  Process options
	int opt;
	int verbose=0;
	while ((opt=getopt(argc,argv,"v"))!=-1)
	{
		if (opt=='v')
			verbose++;
		else
			Fatal("Usage: [-v] <Array Length, Recommend 10-100> <Block Size, Recommend 4>\n");
	}
	argc -= optind;
	argv += optind;

	//  Get desired array size
	if (argc!=2) Fatal("Usage: [-v] <Array Length, Recommend 10-100> <Block Size, Recommend 4>\n");
	int arraySize = atoi(argv[0]);		// Number of elements in arrays
	if (arraySize<1) Fatal("Desired array length out of range %d\n",arraySize);

	// Get desired block size
	int blockSize = atoi(argv[1]);
	if (blockSize<1) Fatal("Desired block size out of range %d\n",blockSize);

	int blocks = arraySize/blockSize + (arraySize%blockSize == 0 ? 0:1);
	printf("Array Length=%d, Block Size=%d, Number of Blocks = %d\n",arraySize,blockSize, blocks);

	//  Initialize GPU
	int Mw = InitGPU(verbose);
	if (Mw<arraySize*blockSize) Fatal("Thread count %d exceeds threads per block of %d\n",blockSize*blockSize,Mw);

	// Allocate arrays
	float *hostArray, *deviceArray, *deviceArray_HostCopy;  // Pointer to host & device arrays
	size_t size = arraySize * sizeof(float);				// Get desired size
	hostArray = (float *)malloc(size);        				// Allocate array on host
	deviceArray_HostCopy = (float *)malloc(size);   		// Allocate array on host to store results from device
	cudaMalloc((void **) &deviceArray, size);   			// Allocate array on device
	if (!hostArray || !deviceArray_HostCopy) Fatal("Cannot allocate host memory\n");

	// Initialize host array and copy it to CUDA device
	// Array filled with sequential numbers
	for (int i=0; i<arraySize; i++) hostArray[i] = (float)i;
	cudaMemcpy(deviceArray, hostArray, size, cudaMemcpyHostToDevice);

	// Do calculation on device:
	Elapsed();
	squareDevice <<< blocks, blockSize >>> (deviceArray, desiredSize);
	if (cudaGetLastError()) Fatal("Kernel execution failed\n");
	double deviceTime = Elapsed();

	// Do calculation on host
	Elasped();
	squareHost(hostArray, arraySize);
	double hostTime = Elaspsed();

	// Retrieve result from device and store it in host array
	 cudaMemcpy(deviceArray_HostCopy, deviceArray, sizeof(float)*arraySize, cudaMemcpyDeviceToHost);

	//  Compute difference between host and device arrays
	double r2=0;
	for (int i=0;i<arraySize;i++)
		r2 += fabs(deviceArray_HostCopy[i]-hostArray[i]);
	r2 /= arraySize;

	// Cleanup
	free(hostArray);
	free(deviceArray_HostCopy);
	cudaFree(deviceArray);

	//  Print results
	printf("Host Time = %6.3f s\n",hostTime);
	printf("Device Time = %6.3f s\n",deviceTime);
	printf("Speedup = %.1f\n",hostTime/deviceTime);
	printf("Difference = %.2e\n",r2);
}
