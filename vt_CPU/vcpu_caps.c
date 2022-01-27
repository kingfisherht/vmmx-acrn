#include <linux/module.h>
#include <linux/init.h>  
#include <linux/kernel.h> 

#include "./include/cpu_caps.h"

MODULE_LICENSE("GPL");
static struct cpu_capability {
	uint8_t apicv_features;
	uint8_t ept_features;

	uint32_t vmx_ept;
	uint32_t vmx_vpid;
	uint32_t core_caps;	/* value of MSR_IA32_CORE_CAPABLITIES */
} cpu_caps;

static struct vcpuinfo_x86 vboot_cpu_data;

void init_pcpu_capabilities(void){
	uint32_t eax, unused;
	uint32_t family_id, model_id, displayfamily, displaymodel;
    cpuid_subleaf(CPUID_VENDORSTRING, 0x0U,
		&vboot_cpu_data.cpuid_level,
		&unused, &unused, &unused);

	cpuid_subleaf(CPUID_FEATURES, 0x0U, &eax, &unused,
		&vboot_cpu_data.cpuid_leaves[FEAT_1_ECX],
		&vboot_cpu_data.cpuid_leaves[FEAT_1_EDX]);

 	/* SDM Vol.2A 3-211 states the algorithm to calculate DisplayFamily and DisplayModel */
	family_id = (eax >> 8U) & 0xfU;
	displayfamily = family_id;
	if (family_id == 0xFU) {
		displayfamily += ((eax >> 20U) & 0xffU);
	}
    vboot_cpu_data.displayfamily = (uint8_t)displayfamily;
}

void init_pcpu_model_name(void)
{
	cpuid_subleaf(CPUID_EXTEND_FUNCTION_2, 0x0U,
		(uint32_t *)(vboot_cpu_data.model_name),
		(uint32_t *)(&vboot_cpu_data.model_name[4]),
		(uint32_t *)(&vboot_cpu_data.model_name[8]),
		(uint32_t *)(&vboot_cpu_data.model_name[12]));
	cpuid_subleaf(CPUID_EXTEND_FUNCTION_3, 0x0U,
		(uint32_t *)(&vboot_cpu_data.model_name[16]),
		(uint32_t *)(&vboot_cpu_data.model_name[20]),
		(uint32_t *)(&vboot_cpu_data.model_name[24]),
		(uint32_t *)(&vboot_cpu_data.model_name[28]));
	cpuid_subleaf(CPUID_EXTEND_FUNCTION_4, 0x0U,
		(uint32_t *)(&vboot_cpu_data.model_name[32]),
		(uint32_t *)(&vboot_cpu_data.model_name[36]),
		(uint32_t *)(&vboot_cpu_data.model_name[40]),
		(uint32_t *)(&vboot_cpu_data.model_name[44]));

	vboot_cpu_data.model_name[48] = '\0';
    printk("pcpu name:%s\n",vboot_cpu_data.model_name);
}

void init_pcpu_pre(void){
    
	init_pcpu_capabilities();
    init_pcpu_model_name();

}