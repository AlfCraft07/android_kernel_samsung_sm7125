// SPDX-License-Identifier: GPL-2.0
/*
 * In-kernel ION to DMA-BUF Heap Wrapper for Qualcomm MSM
 */

#include <linux/dma-buf.h>
#include <linux/dma-heap.h>
#include <linux/err.h>
#include <linux/module.h>
#include <linux/slab.h>

#include "../../staging/android/ion/ion.h"
#include "../../staging/android/uapi/msm_ion.h"

struct ion_heap_wrapper_entry {
	const char *dma_heap_name;
	unsigned int ion_heap_id;
	unsigned int default_flags;
};

/*
 * Mapping of modern AOSP/QTI DMA-BUF heap names to legacy 4.14 ION heaps
 */
static const struct ion_heap_wrapper_entry wrapper_entries[] = {
	{
		.dma_heap_name = "qcom,display",
		.ion_heap_id   = ION_CP_MM_HEAP_ID,
		.default_flags = 0,
	},
	{
		.dma_heap_name = "qcom,secure-display",
		.ion_heap_id   = ION_SECURE_DISPLAY_HEAP_ID,
		.default_flags = ION_FLAG_CP_SEC_DISPLAY,
	},
	{
		.dma_heap_name = "qcom,secure",
		.ion_heap_id   = ION_SECURE_HEAP_ID,
		.default_flags = ION_FLAG_SECURE,
	},
	{
		.dma_heap_name = "qcom,camera",
		.ion_heap_id   = ION_CAMERA_HEAP_ID,
		.default_flags = 0,
	},
	{
		.dma_heap_name = "qcom,audio",
		.ion_heap_id   = ION_AUDIO_HEAP_ID,
		.default_flags = 0,
	},
};

static struct dma_buf *ion_wrapper_allocate(struct dma_heap *heap,
					    unsigned long len,
					    unsigned long fd_flags,
					    unsigned long heap_flags)
{
	const struct ion_heap_wrapper_entry *entry = dma_heap_get_drvdata(heap);
	unsigned int alloc_flags = entry->default_flags;

	/* If caller requests cached, apply ION_FLAG_CACHED */
	if (heap_flags & 0x1)
		alloc_flags |= ION_FLAG_CACHED;

	return ion_alloc(len, (1U << entry->ion_heap_id), alloc_flags);
}

static const struct dma_heap_ops ion_wrapper_heap_ops = {
	.allocate = ion_wrapper_allocate,
};

static int __init ion_wrapper_heap_init(void)
{
	struct dma_heap_export_info exp_info;
	int i;

	for (i = 0; i < ARRAY_SIZE(wrapper_entries); i++) {
		exp_info.name = wrapper_entries[i].dma_heap_name;
		exp_info.ops = &ion_wrapper_heap_ops;
		exp_info.priv = (void *)&wrapper_entries[i];

		dma_heap_add(&exp_info);
		pr_info("ion_wrapper: registered /dev/dma_heap/%s -> ION heap %u\n",
			wrapper_entries[i].dma_heap_name,
			wrapper_entries[i].ion_heap_id);
	}

	return 0;
}
/* Late init ensures ION has fully probed and registered all device tree heaps first */
late_initcall(ion_wrapper_heap_init);

MODULE_DESCRIPTION("Qualcomm ION to DMA-BUF Heap Wrapper");
MODULE_LICENSE("GPL v2");