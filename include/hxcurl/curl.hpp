#ifndef __HX_CURL_HPP
#define __HX_CURL_HPP

#ifdef __cplusplus
extern "C" {
#endif

/*
 *
 */
inline char* malloc_curl_errbuf(void)
{
    char* errbuf = (char*)malloc(sizeof(char) * (CURL_ERROR_SIZE + 1));
    errbuf[CURL_ERROR_SIZE] = '\0';

    return errbuf;
}


/*
 *
 */
inline void root_set(AutoGCRoot** root, value val)
{
    if (root != NULL) {
        if (*root == NULL) {
            *root = new AutoGCRoot(val);
        } else {
            (*root)->set(val);
        }
    }
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* __HX_CURL_HPP */
