void func1(int a, int b){
    printf(a);
    printf(b);
}
int func2(int c, int d) {
    func1(c+d, c-d);
    return (c*d);
}
void main() {
    const int n=10;
    int i, ans;
    i=0;
    ans = 0;
    while (i<n) {
        ans= ans +func2(3+ans, 3-ans);
    }
}
