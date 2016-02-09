
#define to_binary(x) (byte *) \
 (((byte*)(x)) + sizeof(struct ttfunction))

#define to_tf(x) (struct ttfunction *) \
 (((byte*)(x)) - sizeof(struct ttfunction))

