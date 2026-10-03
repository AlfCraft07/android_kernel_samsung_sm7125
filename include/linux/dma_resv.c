#ifndef _LINUX_DMA_RESV_H
#define _LINUX_DMA_RESV_H

#include <linux/reservation.h>

/* Map modern 5.15 naming back to 4.14 infrastructure */
#define dma_resv reservation_object
#define dma_resv_lock(obj, ctx) ww_mutex_lock(&(obj)->lock, ctx)
#define dma_resv_unlock(obj) ww_mutex_unlock(&(obj)->lock)
#define dma_resv_held(obj) ww_mutex_is_locked(&(obj)->lock)
#define dma_resv_assert_held(obj) WARN_ON(!ww_mutex_is_locked(&(obj)->lock))

#endif /* _LINUX_DMA_RESV_H */