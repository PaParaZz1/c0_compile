int x;
int add() {
    x = x + 1;
    return (x);
}
void func(int a, int b, int c) {
    printf(a);
    printf(b);
    printf(c);
    printf(x);
    printf("end");
}
void main() {
    x = 0;
    func(x, x+1, x);
}
