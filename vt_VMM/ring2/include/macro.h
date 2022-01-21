#define MSR_IA32_FEATURE_CONTROL 		0x03a
#define MSR_IA32_VMX_BASIC              0x480
#define MSR_IA32_FEATURE_CONTROL		0x0000003AU
#define CR0_NE                  (1UL<<5U)	/* numeric error */


/* FEATURE CONTROL bits */
#define MSR_IA32_FEATURE_CONTROL_LOCK		(1U << 0U)
#define MSR_IA32_FEATURE_CONTROL_VMX_SMX	(1U << 1U)
#define MSR_IA32_FEATURE_CONTROL_VMX_NO_SMX	(1U << 2U)
#define MSR_IA32_FEATURE_CONTROL_SENTERS_MSK	(0x7F00U)
#define MSR_IA32_FEATURE_CONTROL_SENTER		(1U << 15U)
#define MSR_IA32_FEATURE_CONTROL_SGX_LC		(1U << 17U)
#define MSR_IA32_FEATURE_CONTROL_SGX_GE		(1U << 18U)