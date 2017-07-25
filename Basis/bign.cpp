/*
 * @Author: http://blog.csdn.net/z451483807/article/details/19289891 
 * @Date: 2017-07-24 23:38:30 
 * @Last Modified by:   hgz 
 * @Last Modified time: 2017-07-24 23:38:30 
 */
struct bign
{
    int num[1000 + 10], len;
    bign()
    {
        memset(num, 0, sizeof(num));
        len = 1;
    }
    bign operator=(int x)
    {
        len = 0;
        while (x)
        {
            num[len++] = x % M;
            x /= M;
        }
        if (len == 0)
            len = 1;
        return *this;
    }
    bign operator=(const bign &b)
    {
        len = b.len;
        for (int i = 0; i < len; i++)
            num[i] = b.num[i];
        return *this;
    }
    bign operator+(int x)
    {
        bign c;
        c = *this;
        c.num[0] = c.num[0] + x;
        int temp = c.num[0] / M;
        c.num[0] = c.num[0] % M;
        int i = 1;
        while (temp)
        {
            c.num[i] = c.num[i] + temp;
            temp = c.num[i] / M;
            c.num[i] = c.num[i] % M;
            i++;
        }
        if (i > c.len)
            c.len = i;
        return c;
    }
    bign operator*(int x)
    {
        bign c;
        c.len = len;
        for (int i = 0; i < c.len; i++)
            c.num[i] = num[i] * x;
        int temp = 0;
        for (int i = 0; i < c.len; i++)
        {
            c.num[i] += temp;
            temp = c.num[i] / M;
            c.num[i] = c.num[i] % M;
            if (i == c.len - 1 && temp != 0)
                c.len++;
        }
        while (c.len && c.num[c.len - 1] == 0)
            c.len--;
        if (c.len == 0)
            c.len = 1;
        return c;
    }
    bign operator*(const bign &b)
    {
        bign c;
        c.len = len + b.len - 1;
        for (int i = 0; i < len; i++)
        {
            for (int j = 0; j < b.len; j++)
            {
                c.num[i + j] += num[i] * b.num[j];
            }
        }
        int temp = 0;
        for (int i = 0; i < c.len; i++)
        {
            c.num[i] += temp;
            temp = c.num[i] / M;
            c.num[i] = c.num[i] % M;
            if (i == c.len - 1 && temp != 0)
                c.len++;
        }
        while (c.len && c.num[c.len - 1] == 0)
            c.len--;
        if (c.len == 0)
            c.len = 1;
        return c;
    }
    bign operator-(const bign &b)
    {
        bign c;
        c.len = len;
        int temp = 0;
        for (int i = 0; i < c.len; i++)
        {
            if (num[i] - temp < b.num[i])
            {
                c.num[i] = num[i] - temp + M - b.num[i];
                temp = 1;
            }
            else
            {
                c.num[i] = num[i] - temp - b.num[i];
                temp = 0;
            }
        }
        while (c.len && c.num[c.len - 1] == 0)
            c.len--;
        if (c.len == 0)
            c.len = 1;
        return c;
    }
    void print()
    {
        printf("%d", num[len - 1]);
        for (int i = len - 2; i >= 0; i--)
        {
            printf("%03d", num[i]);
        }
        printf("\n");
    }
};