#pragma once
char* loadIniFile (char *file) {
    char *buffer = 0x0;;
    struct stat stat_buf;
    FILE * pFile = 0x0;;
    size_t size;
    int rc = stat(file, &stat_buf);
    if (rc == 0) {
        pFile = fopen (file,"rt");
        if (pFile != NULL) {
            buffer = (char *) malloc(stat_buf.st_size + 1);
            size = fread(buffer,1, stat_buf.st_size, pFile);
            if (size != stat_buf.st_size) rc = -1;
            buffer[stat_buf.st_size] = 0x0;
        } else {
            rc = -1;
        }
     }
     if (pFile) fclose(pFile);
     if (rc != 0) throw new exception("File not found ");
     return buffer;
}

