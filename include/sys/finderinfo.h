#ifndef FINDERINFO_H
#define FINDERINFO_H


struct FndrExtendedDirInfo {
        u_int32_t document_id;
        u_int32_t date_added;
        u_int16_t extended_flags;
        u_int16_t reserved3;
        u_int32_t write_gen_counter;
} __attribute__((aligned(2), packed));

struct FndrExtendedFileInfo {
        u_int32_t document_id;
        u_int32_t date_added;
        u_int16_t extended_flags;
        u_int16_t reserved2;
        u_int32_t write_gen_counter;
} __attribute__((aligned(2), packed));

/* Finder information */
struct FndrFileInfo {
        u_int32_t       fdType;         /* file type */
        u_int32_t       fdCreator;      /* file creator */
        u_int16_t       fdFlags;        /* Finder flags */
        struct {
            int16_t     v;              /* file's location */
            int16_t     h;
        } fdLocation;
        int16_t         opaque;
} __attribute__((aligned(2), packed));
typedef struct FndrFileInfo FndrFileInfo;



#endif
