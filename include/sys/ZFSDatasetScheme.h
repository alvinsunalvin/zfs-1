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
 * Copyright (c) 2016, Evan Susarret.  All rights reserved.
 */

#ifndef ZFSDATASETSCHEME_H_INCLUDED
#define	ZFSDATASETSCHEME_H_INCLUDED

#define	kZFSDatasetSchemeClass	"ZFSDatasetScheme"

#include <IOKit/storage/IOPartitionScheme.h>
#include <sys/ZFSDataset.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int zfs_osx_proxy_get_osname(const char *bsdname,
    char *osname, int len);
int zfs_osx_proxy_get_bsdname(const char *osname,
    char *bsdname, int len);


void zfs_osx_proxy_remove(const char *osname);
int zfs_osx_proxy_create(const char *osname);

#ifdef __cplusplus
} /* extern "C" */

/* Not C external */
ZFSDataset * zfs_osx_proxy_get(const char *osname);

class ZFSDatasetScheme : public IOPartitionScheme
{
	OSDeclareDefaultStructors(ZFSDatasetScheme);
public:

	virtual void free(void);
	virtual bool init(OSDictionary *properties);
	virtual bool start(IOService *provider);
	virtual IOService *probe(IOService *provider, SInt32 *score);

	bool addDataset(const char *osname);
	bool removeDataset(const char *osname, bool force);

	/* Compatibility shims */
	virtual void read(IOService *client,
	    UInt64		byteStart,
	    IOMemoryDescriptor	*buffer,
	    IOStorageAttributes	*attributes,
	    IOStorageCompletion	*completion);

	virtual void write(IOService *client,
	    UInt64		byteStart,
	    IOMemoryDescriptor	*buffer,
	    IOStorageAttributes	*attributes,
	    IOStorageCompletion	*completion);

	virtual IOReturn synchronize(IOService *client,
	    UInt64			byteStart,
	    UInt64			byteCount,
	    IOStorageSynchronizeOptions	options = 0);

	virtual IOReturn unmap(IOService *client,
	    IOStorageExtent		*extents,
	    UInt32			extentsCount,
	    IOStorageUnmapOptions	options = 0);

	virtual bool lockPhysicalExtents(IOService *client);

	virtual IOStorage *copyPhysicalExtent(IOService *client,
	    UInt64 *    byteStart,
	    UInt64 *    byteCount);

	virtual void unlockPhysicalExtents(IOService *client);

	virtual IOReturn setPriority(IOService *client,
	    IOStorageExtent	*extents,
	    UInt32		extentsCount,
	    IOStoragePriority	priority);

protected:
private:
	OSSet		*_datasets;
	OSOrderedSet	*_holes;
	uint64_t	_max_id;

	uint32_t getNextPartitionID();
	void returnPartitionID(uint32_t part_id);
};

#endif /* __cplusplus */
#endif /* ZFSDATASETSCHEME_H_INCLUDED */
