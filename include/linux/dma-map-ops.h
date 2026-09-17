/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_DMA_MAP_OPS_H
#define _LINUX_DMA_MAP_OPS_H

#include <linux/dma-mapping.h>
#include <linux/dma-contiguous.h>
#include <linux/scatterlist.h>
#include <linux/highmem.h>

/* scatterlist iterators (introduced in 5.8) */
#ifndef for_each_sgtable_sg
#define for_each_sgtable_sg(sgt, sg, i) \
	for_each_sg((sgt)->sgl, sg, (sgt)->orig_nents, i)
#endif

#ifndef for_each_sgtable_page
#define for_each_sgtable_page(sgt, iter, pgoff) \
	for_each_sg_page((sgt)->sgl, iter, (sgt)->orig_nents, pgoff)
#endif

/* kmap_local replacements (introduced in 5.11 to replace kmap_atomic) */
#ifndef kmap_local_page
#define kmap_local_page(page)	kmap_atomic(page)
#define kunmap_local(addr)	kunmap_atomic(addr)
#endif

#ifndef page_size
#define page_size(page) (PAGE_SIZE << compound_order(page))
#endif

/* sgtable dma wrappers (introduced in 5.8) */
static inline int dma_map_sgtable(struct device *dev, struct sg_table *sgt,
				  enum dma_data_direction dir, unsigned long attrs)
{
	int nents;

	nents = dma_map_sg_attrs(dev, sgt->sgl, sgt->orig_nents, dir, attrs);
	if (nents <= 0)
		return -EINVAL;

	sgt->nents = nents;
	return 0;
}

static inline void dma_unmap_sgtable(struct device *dev, struct sg_table *sgt,
				    enum dma_data_direction dir, unsigned long attrs)
{
	dma_unmap_sg_attrs(dev, sgt->sgl, sgt->orig_nents, dir, attrs);
}

static inline void dma_sync_sgtable_for_cpu(struct device *dev,
					    struct sg_table *sgt,
					    enum dma_data_direction dir)
{
	dma_sync_sg_for_cpu(dev, sgt->sgl, sgt->orig_nents, dir);
}

static inline void dma_sync_sgtable_for_device(struct device *dev,
					       struct sg_table *sgt,
					       enum dma_data_direction dir)
{
	dma_sync_sg_for_device(dev, sgt->sgl, sgt->orig_nents, dir);
}

#endif /* _LINUX_DMA_MAP_OPS_H */