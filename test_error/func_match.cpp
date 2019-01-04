int func(int a, int b) {
    return (a+b);
}
char func2(char c,int a, char d)
{}
void main() {
    const char c='a';
    int a;
    char c1;
    char char;
    c1='r';
    func(1,2,3);
    func(1,2);
    func(1);
    a=func(1,2);
    a=func(1,2,3);
    a=func('a',2);
    a=func(('a'),2);
    a=func('a'+'b',2);
    a=func('a'*2,2);
    a=func(-'a',2);
    a=func2(c1,2,c1);
    a=func2(c,a,c1);
    a=func(c,a);
    func(c1,c);
}
