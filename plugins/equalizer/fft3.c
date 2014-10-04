#include <stdlib.h>
#include <math.h>
#include <fftw3.h>

void fft3_forward(float* buf, int len, int N, float* re, float* im, int stride){
	float* in;
	fftwf_complex* out;
	fftwf_plan p;
	int i;

	in = (float*) fftwf_malloc(sizeof(float) * len);
	out = (fftwf_complex*) fftwf_malloc(sizeof(fftwf_complex) * len);

	for(i=0; i<len; i++){
		in[i] = buf[i * stride];
	}

	p = fftwf_plan_dft_r2c_1d(len, in, out, FFTW_MEASURE);

	fftwf_execute(p);

	for(i=0; i<len; i++){
		re[i] = out[i][0];
		im[i] = out[i][1];
	}

	fftwf_destroy_plan(p);
	fftwf_free(in);
	fftwf_free(out);
}

void fft3_inverse(float* re, float* im, int len, int N, float* buf, int stride){
	fftwf_complex* in;
	float* out;
	fftwf_plan p;
	int i;

	in = (fftwf_complex*) fftwf_malloc(sizeof(fftwf_complex) * len);
	out = (float*) fftwf_malloc(sizeof(float) * len);

	for(i=0; i<len; i++){
		in[i][0] = re[i];
		in[i][1] = im[i];
	}

	p = fftwf_plan_dft_c2r_1d(len, in, out, FFTW_MEASURE);

	fftwf_execute(p);

	for(i=0; i<len; i++){
		buf[i * stride] = out[i] / (float)len;
	}

	fftwf_destroy_plan(p);
	fftwf_free(in);
	fftwf_free(out);
}
