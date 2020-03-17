//==============================================================
// Copyright © 2019 Intel Corporation
//
// SPDX-License-Identifier: MIT
// =============================================================

#include <CL/sycl.hpp>

#include <array>
#include <iostream>
#include <string>
#include <CL/sycl/intel/fpga_extensions.hpp>

const std::string info_to_string(const cl::sycl::info::device_type info) {
	switch (info) {
	case cl::sycl::info::device_type::cpu:
		return "cpu";
	case cl::sycl::info::device_type::gpu:
		return "gpu";
	case cl::sycl::info::device_type::accelerator:
		return "accelerator";
	case cl::sycl::info::device_type::custom:
		return "custom";
	case cl::sycl::info::device_type::automatic:
		return "automatic";
	case cl::sycl::info::device_type::host:
		return "host";
	case cl::sycl::info::device_type::all:
		return "all";
	}
}
int main() {
	class MyDeviceSelector : public cl::sycl::device_selector {
	public:
		int operator()(const cl::sycl::device& Device) const override {
			using namespace cl::sycl::info;
			const std::string DeviceName = Device.get_info<device::name>();
			const std::string DeviceVendor = Device.get_info<device::vendor>();
			const auto DeviceType = Device.get_info<device::device_type>();
			const std::string Type = info_to_string(DeviceType);
			std::cout << DeviceVendor << " " << DeviceName << " (" << Type << ")" << std::endl;
			return 1;
		}
	};

	MyDeviceSelector Selector;
	try
	{
		cl::sycl::queue Queue(Selector);
	}
	catch (cl::sycl::invalid_parameter_error & E) 
	{
		std::cout << E.what() << std::endl;
	}
}
