/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */
/*
 * Copyright 2007 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 * Portions Copyright 2007 Apple Inc. All rights reserved.
 * Use is subject to license terms.
 * Copyright (C) 2008-2010 Lawrence Livermore National Security, LLC.
 * Produced at Lawrence Livermore National Laboratory (cf, DISCLAIMER).
 * Rewritten for Linux by Brian Behlendorf <behlendorf1@llnl.gov>.
 * LLNL-CODE-403049.
 * Copyright (c) 2013 by Delphix. All rights reserved.
 */

#include <sys/zfs_context.h>
#include <sys/spa.h>
#include <sys/vdev_iokit.h>
#include <sys/vdev_impl.h>
#include <sys/fs/zfs.h>
#include <sys/zio.h>
#ifdef __APPLE__
#include <sys/mount.h>
#else
#include <sys/sunldi.h>
#endif /*__APPLE__*/


unsigned int zfs_iokit_vdev_ashift = 0;


/*
 * Virtual device vector for disks via Mac OS X IOKit.
 */

static int
vdev_iokit_open(vdev_t *vd, uint64_t *size, uint64_t *max_size, uint64_t *ashift)
{
	//vnode_t *devvp = NULLVP;  /* Old device vnode */
//	vfs_context_t context = NULL;
//	uint64_t blkcnt;
//	uint32_t blksize;
//	int fmode = 0;
	int error = 0;
vdev_iokit_log_ptr( "vdev_iokit_open: vd:",         vd );
vdev_iokit_log_num( "vdev_iokit_open: size:",       *size );
vdev_iokit_log_num( "vdev_iokit_open: maxsize:",    *max_size );
vdev_iokit_log_num( "vdev_iokit_open: ashift:",     *ashift );
	/*
	 * We must have a pathname, and it must be absolute.
	 */
	if (vd->vdev_path == NULL || vd->vdev_path[0] != '/') {
		vd->vdev_stat.vs_aux = VDEV_AUX_BAD_LABEL;
		return (EINVAL);
	}

    /*
     * ### APPLE TODO ###
     *
     *  XXX - This may need to be handled a bit differently for
     *   changed device paths, possibly referencing the vdev by GUID
     */
	/*
	 * When opening a disk device, we want to preserve the user's original
	 * intent.  We always want to open the device by the path the user gave
	 * us, even if it is one of multiple paths to the save device.  But we
	 * also want to be able to survive disks being removed/recabled.
	 * Therefore the sequence of opening devices is:
	 *
	 * 1. Try opening the device by path.  For legacy pools without the
	 *    'whole_disk' property, attempt to fix the path by appending 's0'.
	 *
	 * 2. If the devid of the device matches the stored value, return
	 *    success.
	 *
	 * 3. Otherwise, the device may have moved.  Try opening the device
	 *    by the devid instead.
	 *
	 */
    


    
    /*
     *  XXX - Replace with IOKit lookup -
     *       currently in vdev_iokit_util.cpp
     *
     *   1 physpath - IOService path, or file path
     *   2 path - file path
     *   3 guid - vdev guid
     */
	/* ### APPLE TODO ### */
	/* ddi_devid_str_decode */
    
    /* No longer needed as-is, do IOKit initialization here if necessary */
    /*
	context = vfs_context_create((vfs_context_t)0);
     */
    
    /*
     *  XXX - Obtain an opened/referenced IOKit handle for the device
     */
	/* Obtain an opened/referenced vnode for the device. */
    /*
	error = vnode_open(vd->vdev_path, spa_mode(vd->vdev_spa), 0, 0, &devvp, context);
	if (error) {
		goto out;
	}
     */

    error = vdev_iokit_handle_open( vd, size, max_size, ashift);
    if (error != 0) {
		goto out;
	}
    
    /*
     if (!vnode_isblk(devvp)) {
     error = ENOTBLK;
     goto out;
     }
     */

    
    
    /*
     *  XXX - This will not be necessary through IOKit
     */
	/* ### APPLE TODO ### */
	/* vnode_authorize devvp for KAUTH_VNODE_READ_DATA and
	 * KAUTH_VNODE_WRITE_DATA
	 */

    /*
     *  XXX - Not necessary here - however this must be
     *   handled by IOKit when opening the device
     */
	/*
	 * Disallow opening of a device that is currently in use.
	 * Flush out any old buffers remaining from a previous use.
	 */
    /*
	if ((error = vfs_mountedon(devvp))) {
		goto out;
	}
	if (VNOP_FSYNC(devvp, MNT_WAIT, context) != 0) {
		error = ENOTBLK;
		goto out;
	}
	if ((error = buf_invalidateblks(devvp, BUF_WRITE_DATA, 0, 0))) {
		goto out;
	}
     */
    
    /*
     *  XXX - Much simpler call can get this info from IOKit
     */
	/*
	 * Determine the actual size of the device.
	 */
    /*
	if (VNOP_IOCTL(devvp, DKIOCGETBLOCKSIZE, (caddr_t)&blksize, 0, context)
	       	!= 0 || VNOP_IOCTL(devvp, DKIOCGETBLOCKCOUNT, (caddr_t)&blkcnt,
		0, context) != 0) {

		error = EINVAL;
		goto out;
	}
	*size = blkcnt * (uint64_t)blksize;
     */

	/*
	 *  ### APPLE TODO ###
	 * If we own the whole disk, try to enable disk write caching.
	 */

    /* Also handle in IOKit open */
	/*
	 * Take the device's minimum transfer size into account.
	 */
	//*ashift = highbit(MAX(blksize, SPA_MINBLOCKSIZE)) - 1;

    /*
     *  XXX - check
     */
    /*
     * Setting the vdev_ashift did in fact break the pool for import
     * on ZEVO. This puts the logic into question. It appears that vdev_top
     * will also then change. It then panics in space_map from metaslab_alloc
     */
    //vd->vdev_ashift = *ashift;
    //dvd->vd_ashift = *ashift;

    /*
     *  XXX - As-is but remove devvp
     */
	/*
	 * Clear the nowritecache bit, so that on a vdev_reopen() we will
	 * try again.
	 */
    
    /*
	dvd->vd_devvp = devvp;
     */
out:
	if (error) {
        /*
		if (devvp)
			vnode_close(devvp, fmode, context);
         */

		/*
		 * Since the open has failed, vd->vdev_tsd should
		 * be NULL when we get here, signaling to the
		 * rest of the spa not to try and reopen or close this device
		 */
		vd->vdev_stat.vs_aux = VDEV_AUX_OPEN_FAILED;
	}
    /*
     *  XXX - No longer needed
     */
    /*
	if (context) {
		(void) vfs_context_rele(context);
	}
     */
	return (error);
}

static void
vdev_iokit_close(vdev_t *vd)
{
	vdev_iokit_t *dvd = vd->vdev_tsd;
vdev_iokit_log_ptr( "vdev_iokit_close: vd:",    vd );
	if (dvd == NULL)
		return;
    
    /*
     *  XXX - Replace with IOKit handle close
     */
    
    vdev_iokit_handle_close( vd );
    
/*
	if (dvd->vd_devvp != NULL) {
		vfs_context_t context;

		context = vfs_context_create((vfs_context_t)0);

		(void) vnode_close(dvd->vd_devvp, spa_mode(vd->vdev_spa), context);
		(void) vfs_context_rele(context);

	}
*/
    
	kmem_free(dvd, sizeof (vdev_iokit_t));
	vd->vdev_tsd = NULL;
}

void
vdev_iokit_ioctl_done(void *zio_arg, const int error)
{
vdev_iokit_log_ptr( "vdev_iokit_ioctl_done: zio_arg:",    zio_arg );
vdev_iokit_log_num( "vdev_iokit_ioctl_done: error:",      error );
	zio_t *zio = zio_arg;

	zio->io_error = error;

	//zio_next_stage_async(zio);
    zio_interrupt(zio);
}

static int
vdev_iokit_io_start(zio_t *zio)
{
	vdev_t *vd = zio->io_vd;
//	vdev_iokit_t *dvd = vd->vdev_tsd;
//	struct buf *bp;
//	vfs_context_t context;
	int error = 0;
vdev_iokit_log_ptr( "vdev_iokit_io_start: zio:", zio );
	if (zio->io_type == ZIO_TYPE_IOCTL) {
		zio_vdev_io_bypass(zio);

		/* XXPOLICY */
		if (vdev_is_dead(vd)) {
			zio->io_error = ENXIO;
			//zio_next_stage_async(zio);
			return (ZIO_PIPELINE_CONTINUE);
            //return;
		}

		switch (zio->io_cmd) {

		case DKIOCFLUSHWRITECACHE:

			if (zfs_nocacheflush)
				break;

			if (vd->vdev_nowritecache) {
				zio->io_error = SET_ERROR(ENOTSUP);
				break;
			}

            /*
             *  XXX - No context needed
             */
            /*
			context = vfs_context_create((vfs_context_t)0);
             */
                
            /*
             *  XXX - Replace with IOKit ioctl passthrough
             */
            /*
			error = VNOP_IOCTL(dvd->vd_devvp, DKIOCSYNCHRONIZECACHE, NULL, FWRITE, context);
             */
                
            vdev_iokit_sync( vd, zio );
                
//
//
//            vdev_iokit_ioctl( vd, zio );
//
//
            /*
             *  XXX - No context needed
             */
            /*
			(void) vfs_context_rele(context);
             */
                
			if (error == 0)
				vdev_iokit_ioctl_done(zio, error);
			else
				error = ENOTSUP;

			if (error == 0) {
				/*
				 * The ioctl will be done asychronously,
				 * and will call vdev_iokit_ioctl_done()
				 * upon completion.
				 */
				return ZIO_PIPELINE_STOP;
			} else if (error == ENOTSUP || error == ENOTTY) {
				/*
				 * If we get ENOTSUP or ENOTTY, we know that
				 * no future attempts will ever succeed.
				 * In this case we set a persistent bit so
				 * that we don't bother with the ioctl in the
				 * future.
				 */
				vd->vdev_nowritecache = B_TRUE;
			}
			zio->io_error = error;

			break;

		default:
			zio->io_error = SET_ERROR(ENOTSUP);
		}

		//zio_next_stage_async(zio);
        return (ZIO_PIPELINE_CONTINUE);
	}

	if (zio->io_type == ZIO_TYPE_READ && vdev_cache_read(zio) == 0)
        return (ZIO_PIPELINE_STOP);
    //		return;

	if ((zio = vdev_queue_io(zio)) == NULL)
        return (ZIO_PIPELINE_CONTINUE);
    //		return;

    /*
     *  XXX
     */
//	flags = (zio->io_type == ZIO_TYPE_READ ? B_READ : B_WRITE);
	//flags |= B_NOCACHE;

//	if (zio->io_flags & ZIO_FLAG_FAILFAST)
//		flags |= B_FAILFAST;

	/*
	 * Check the state of this device to see if it has been offlined or
	 * is in an error state.  If the device was offlined or closed,
	 * dvd will be NULL and buf_alloc below will fail
	 */
	//error = vdev_is_dead(vd) ? ENXIO : vdev_error_inject(vd, zio);
	if (vdev_is_dead(vd)) {
        error = ENXIO;
    }

	if (error) {
		zio->io_error = error;
		//zio_next_stage_async(zio);
		return (ZIO_PIPELINE_CONTINUE);
	}

    /*
     *  XXX - Instead pass the zio/flags to IOKit
     */
    /*
	bp = buf_alloc(dvd->vd_devvp);

	ASSERT(bp != NULL);
     */
	ASSERT(zio->io_data != NULL);
	ASSERT(zio->io_size != 0);

    /*
     *  XXX - Instead pass the zio/flags to IOKit
     */
    /*
	buf_setflags(bp, flags);
	buf_setcount(bp, zio->io_size);
	buf_setdataptr(bp, (uintptr_t)zio->io_data);
     */

    /*
     *  XXX - Instead calculate this in IOKit if needed
     */
    /*
    if (zfs_iokit_vdev_ashift && vd->vdev_ashift) {
        buf_setlblkno(bp, zio->io_offset>>vd->vdev_ashift);
        buf_setblkno(bp,  zio->io_offset>>vd->vdev_ashift);
    } else {
        buf_setlblkno(bp, lbtodb(zio->io_offset));
        buf_setblkno(bp, lbtodb(zio->io_offset));
    }
     */
    
    /*
     *  XXX - Instead pass the zio/flags to IOKit
     */
    /*
	buf_setsize(bp, zio->io_size);
     */
    
    /*
     *  XXX - Instead pass the callback to IOKit
     */
    /*
	if (buf_setcallback(bp, vdev_iokit_io_intr, zio) != 0)
		panic("vdev_iokit_io_start: buf_setcallback failed\n");
     */
    
    /*
     *  XXX - Instead do the read/write strategy in IOKit
     */
    /*
	if (zio->io_type == ZIO_TYPE_WRITE) {
		vnode_startwrite(dvd->vd_devvp);
	}
	error = VNOP_STRATEGY(bp);
     */
    
    error =     vdev_iokit_strategy( vd, zio );
    
	ASSERT(error == 0);

    return (ZIO_PIPELINE_STOP);
}

static void
vdev_iokit_io_done(zio_t *zio)
{
vdev_iokit_log_ptr( "vdev_iokit_io_done: zio:", zio );
    /*
     *  XXX - TO DO
     *
     *  By attaching to the IOMedia device, we can both check
     *   the status via IOKit functions, and be informed of
     *   device changes.
     *
     *  Call an IOKit helper function to check the IOMedia
     *   device - status, properties, and/or ioctl.
     */
    
#ifndef __APPLE__
	/*
	 * XXX- NOEL TODO
	 * If the device returned EIO, then attempt a DKIOCSTATE ioctl to see if
	 * the device has been removed.  If this is the case, then we trigger an
	 * asynchronous removal of the device.
	 */
	if (zio->io_error == EIO) {
		state = DKIO_NONE;
		if (ldi_ioctl(dvd->vd_lh, DKIOCSTATE, (intptr_t)&state,
                      FKIOCTL, kcred, NULL) == 0 &&
		    state != DKIO_INSERTED) {
			vd->vdev_remove_wanted = B_TRUE;
			spa_async_request(zio->io_spa, SPA_ASYNC_REMOVE);
		}
	}
#endif /* !__APPLE__ */
    
	//zio_next_stage(zio);
}

#if 0
static void
vdev_iokit_io_intr(struct buf *bp, void *arg)
{
vdev_iokit_log_ptr( "vdev_iokit_io_intr: bp:",  bp );
vdev_iokit_log_ptr( "vdev_iokit_io_intr: arg:", arg );
	zio_t *zio = (zio_t *)arg;
    
    zio->io_error = buf_error(bp);
    
	if (zio->io_error == 0 && buf_resid(bp) != 0) {
		zio->io_error = EIO;
	}
	buf_free(bp);
	//zio_next_stage_async(zio);
    zio_interrupt(zio);
}
#endif

vdev_ops_t vdev_iokit_ops = {
	vdev_iokit_open,
	vdev_iokit_close,
	vdev_default_asize,
	vdev_iokit_io_start,
	vdev_iokit_io_done,
	NULL /* vdev_op_state_change */,
	NULL /* vdev_op_hold */,
	NULL /* vdev_op_rele */,
	VDEV_TYPE_DISK,	/* name of this vdev type */
	B_TRUE			/* leaf vdev */
};