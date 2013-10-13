#ifndef DV2549_EXPERIMENT_CONF_H
#define DV2549_EXPERIMENT_CONF_H

#include <string>
#include <windows.h> // Get rid of these.

// This is terrible. Fix.
#ifdef EXPERIMENT_DEBUG
static const LPCWSTR PathKernelTest = L"../../bin/experiment/Debug/KernelTest.cso";
static const LPCWSTR PathKernelMult = L"../../bin/experiment/Debug/KernelMult.cso";
#else
static const LPCWSTR PathKernelTest = L"../../bin/experiment/Release/KernelTest.cso";
static const LPCWSTR PathKernelMult = L"../../bin/experiment/Release/KernelMult.cso";
#endif // EXPERIMENT_DEBUG

static const std::string g_mxgPath = "../../mxg/";
static const std::string g_mxgA = "a.mxg";
static const std::string g_mxgB = "b.mxg";
static const std::string g_mxgC = "c.mxg";
static const std::string g_mxgRef = "ref.mxg";

enum MatrixgenPrecisions {
	MatrixgenPrecisions_INTEGER = 0
};

#endif // DV2549_EXPERIMENT_CONF_H
