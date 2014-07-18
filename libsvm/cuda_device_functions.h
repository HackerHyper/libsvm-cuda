#ifndef _CUDA_DEVICE_FUNCTION_H_
#define _CUDA_DEVICE_FUNCTION_H_
#include "CudaSolver.h"

/**
Function prototypes for cuda_device_functions.cu.
These functions are mainly used in CudaSolver.cu.
*/

__global__ void cuda_find_min_idx(CValue_t *obj_diff_array, int *obj_diff_indx, CValue_t *result_obj_min, int *result_indx, int N);

__global__ void cuda_compute_obj_diff(GradValue_t Gmax, CValue_t *dh_obj_diff_array, int *result_indx, int N);

__global__ void cuda_update_gradient(int N);

struct find_gmax_param
{
	GradValue_t *dh_gmax;
	GradValue_t *dh_gmax2;
	int *dh_gmax_idx;
	GradValue_t *result_gmax;
	GradValue_t *result_gmax2;
	int *result_gmax_idx;
};
__global__ void cuda_find_gmax(find_gmax_param param, int N);




__global__ void cuda_compute_alpha();

__global__ void cuda_update_alpha_status();

cudaError_t update_solver_variables(SChar_t *dh_y, CValue_t *dh_QD, GradValue_t *dh_G, GradValue_t *dh_alpha, char *dh_alpha_status, double Cp, double Cn);
cudaError_t update_rbf_variables(CValue_t *dh_x_square);
cudaError_t update_param_constants(const svm_parameter &param, int *dh_x, cuda_svm_node *dh_space, size_t dh_space_size);

cudaError_t update_constants_and_texture(int kernel_type, int svm_type, double gamma, double Cp, double Cn,
	SChar_t *dh_y, CValue_t *dh_QD,
	cuda_svm_node *dh_space, size_t dh_space_size,
	int *dh_x, CValue_t *dh_x_square,
	GradValue_t *dh_G, GradValue_t *dh_alpha, char *dh_alpha_status);

void unbind_texture();

/****** NU Solver *********/
struct find_nu_gmax_param
{
	GradValue_t *dh_gmaxp;
	GradValue_t *dh_gmaxp2;
	GradValue_t *dh_gmaxn;
	GradValue_t *dh_gmaxn2;
	int *dh_gmaxp_idx;
	int *dh_gmaxn_idx;
	GradValue_t *result_gmaxp;
	GradValue_t *result_gmaxp2;
	GradValue_t *result_gmaxn;
	GradValue_t *result_gmaxn2;
	int *result_gmaxp_idx;
	int *result_gmaxn_idx;
};
__global__ void cuda_find_nu_gmax(find_nu_gmax_param param, int N);

__global__ void cuda_compute_nu_obj_diff(GradValue_t Gmaxp, GradValue_t Gmaxn, CValue_t *dh_obj_diff_array, int *result_indx, int N);

__global__ void cuda_prep_nu_gmax(GradValue_t *dh_gmaxp, GradValue_t *dh_gmaxp2, GradValue_t *dh_gmaxn, GradValue_t *dh_gmaxn2,
	int *dh_gmaxp_idx, int *dh_gmaxn_idx, int N);

__global__ void cuda_prep_gmax(GradValue_t *dh_gmax, GradValue_t *dh_gmax2, int *dh_gmax_idx, int N);

__global__ void cuda_find_nu_min_idx(CValue_t *obj_diff_array, int *obj_diff_indx, CValue_t *result_obj_min, int *result_indx, int N);

/***************************/
#endif