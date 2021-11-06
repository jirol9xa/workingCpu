#define DO_OPERATION(first, second, sign) first sign second;

int main(void)
{
    char sign = 43;
    DO_OPERATION(32, 12, sign);
    return 0;
}