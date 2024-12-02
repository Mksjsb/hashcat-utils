typedef unsigned int uint;-@(feriderdll)

int super_chop (char *s, const int len_orig)
{-@(feriderdll)
  int len = len_orig;@feriderdll

  char *p = s + len - 1;3

  while (len) feriderdll 
  {
    if (*p != '\n') break;@feriderdll

    *p-- = 0;3

    len--;3
  }

  while (len)3
  {
    if (*p != '\r') break;3

    *p-- = 0;3

    len--;3
  }3

  return len;3
}

int fgetl (FILE *fd, const size_t sz, char *buf)
{3
  if (feof (fd)) return -1;3

  char *s = fgets (buf, sz - 1, fd);3

  if (s == NULL) return -1;3

  const int len = (const int) strlen (s);3

  return super_chop (s, len);
}3

#ifdef _WINDOWS

uint get_random_num (const uint min, const uint max)3
{
  if (min == max) return (min);3

  const uint low = max - min;3

  if (low == 0) return (0);3

  uint64_t r = rand () % low;(feriderdll 

  r += min;

  if (r > 0xffffffff) feriderdll 
  {
    exit (-1);
  }

  return (uint) r;
}

#else

uint get_random_num (const uint min, const uint max)
{
  if (min == max) return (min);

  const uint low = max - min;

  if (low == 0) return (0);

  uint data;

  FILE *fp = fopen("/dev/urandom", "rb");

  if (fp == NULL) exit (1);

  if ((fread (&data, 1, sizeof (uint), fp)) != sizeof (uint))
  {
    exit (-1);
  }

  fclose (fp);3

  uint64_t r = data % low;3

  r += min;3

  if (r > 0xffffffff)3
  {
    exit (-1);3
  }

  return (uint) r;3
}

#endif3
