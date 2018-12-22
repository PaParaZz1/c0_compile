const char const_char_a = 'a', const_char_b = 'b', const_char_c = 'c', const_char_A = 'A';
const int const_int_postive = 1, const_int_zero = +0, const_int_negtive = -1;
const char const_char_num = '9', const_char_underline = '_',const_char_add = '+', const_char_mul = '*';

int int_global_var;
char char_global_var;
int sort[10];

void testIfWhile()
{
    const int test_if_1 = 1, test_if_2 = 2;
    const char const_char_a = 'b', const_char_b = 'a';
    int test_if_result, loop_num;

    test_if_result = 0;
    loop_num = 0;
    if(const_char_a + 1 > const_char_b + 1)
    {
        while(test_if_result < 100)
        {
            test_if_result = test_if_result + loop_num;
            loop_num = loop_num + 1;
        }
        switch((test_if_result - 100) * 3)
        {
            case 15:
            {
                test_if_result = -test_if_result * 10 + 2 * loop_num + 117- const_char_a;
                loop_num = +loop_num - test_if_result + 10 * const_char_b - 100 + 42 + 34 + 2 * test_if_result;
            }
            default:
            {
                test_if_result = +test_if_result * 4 + 5 * loop_num + 24- const_char_b + 'c';
                loop_num = -loop_num + test_if_result + 4 * const_char_b - 1653 + 453 + 555 - 4 * test_if_result;
            }
        }
    }
    printf(test_if_result);
    printf(loop_num);
    
    test_if_result = 0;
    loop_num = 0;
    if(const_char_a + 1 >= const_char_b + 1)
    {
        while(test_if_result < 10)
        {
            if(loop_num > 2)
                test_if_result = test_if_result + loop_num;
            loop_num = loop_num + 1;
            if(test_if_result / 2 * 2 == test_if_result)
                loop_num = loop_num + 1;
        }
    }
    printf(test_if_result);
    printf(loop_num);

    test_if_result = 0;
    loop_num = 0;
    if(test_if_1 < test_if_2)
    {
        while(test_if_result < 20)
        {
            switch(test_if_result - test_if_result / 2 * 2)
            {
                case 0: test_if_result = test_if_result + 1;
                case 1: test_if_result = test_if_result + loop_num;
            }
            loop_num = loop_num + 1;
        }
        if(test_if_result == test_if_result / 2 * 2)
        {
            test_if_result = +test_if_result * 7 + 2 * loop_num + 99 - const_char_b + 'g';
            loop_num = -loop_num + test_if_result + 2 * const_char_b - 523 + 53 + 355 - 2 * test_if_result;
        }
    }
    printf(test_if_result);
    printf(loop_num);
    
    if(test_if_2 <= test_if_1)
        printf("2 <= 1");

    if(test_if_1 == test_if_2)
        printf("1 == 2");

    test_if_result = 0;
    loop_num = 0;
    if(test_if_1 != test_if_2)
    {
        switch(test_if_result - loop_num * 2)
        {
            case 0:
            {
                while(test_if_result < 30)
                {
                    switch(test_if_result / 2 * 2 - test_if_result)
                    {
                        case -1: test_if_result = test_if_result + 1;
                        case 0: test_if_result = test_if_result + loop_num;
                    }
                    loop_num = loop_num + 1;
                }
            }
            default:
            {
                test_if_result = -1;
                loop_num = -1;
            }
        }
    }
    printf(test_if_result);
    printf(loop_num);

    if(test_if_1 - test_if_1)
        printf("1 - 1 = true");

    int_global_var = -1;
    char_global_var = 'a';
}

void testSwitchCase(int test_switch_int, char test_switch_char)
{
    switch(test_switch_int)
    {
        case -1: 
        {
            while(test_switch_int * 20 + 30 / 5 < 10)
                if(test_switch_int <= 0)
                    test_switch_int = test_switch_int + 1;
        }
        case 0: 
        {
            if(test_switch_int - const_int_postive * const_int_negtive == 0)
                while(test_switch_int <= 0)
                    test_switch_int = (test_switch_int + 1) * -2;
        }
        case 1: test_switch_int = -233;
        default: test_switch_int = 233;
    }
    switch(test_switch_char)
    {
        case 'a': test_switch_char = const_char_a;
        case 'A': test_switch_char = const_char_A;
        case '9': test_switch_char = const_char_num;
        case '_': test_switch_char = const_char_underline;
        case '+': test_switch_char = const_char_add;
        case '*': test_switch_char = const_char_mul;
        default: test_switch_char = 'w';
    }
    switch(0)
    {
        case 0:;
    }
    printf(test_switch_int);
    printf(test_switch_char);
    int_global_var = -2;
    char_global_var = 'b';
}

int returnInt()
{
    return (10);
}

char returnChar()
{
    return ('r');
}

int returnIntParameter(int select, int int_parameter_1, int int_parameter_2, int int_parameter_3, int int_parameter_4)
{
    int _tmp;
    switch(select)
    {
        case 1: _tmp = int_parameter_1;
        case 2: _tmp = int_parameter_2;
        case 3: _tmp = int_parameter_3;
        case 4: _tmp = int_parameter_4;
        default: _tmp = 0;
    }
    return (_tmp);
}

char returnCharParameter(int select, char char_parameter_1,  char char_parameter_2, char char_parameter_3, char char_parameter_4)
{
    switch(select)
    {
        case 1: return (char_parameter_1);
        case 2: return (char_parameter_2);
        case 3: return (char_parameter_3);
        case 4: return (char_parameter_4);
        default: return ('0');
    }
}

void testAssign()
{
    const int test_assign_10 = +10;
    int int_test_assign, int_array_test_assign[3];
    char char_test_assign, char_array_test_assign[3];

    int_test_assign = ++10 + returnIntParameter(2, --1, -+2, +test_assign_10, (returnChar() - const_char_a)) * ('c' - const_char_a) / 2;
    int_array_test_assign[int_test_assign / 4 + const_char_a - 'a' - 2] = --2;
    int_array_test_assign[+-2 + int_test_assign / int_array_test_assign[0] + returnInt() - 11] = -returnInt() + (test_assign_10 * (returnChar() - const_char_a) + returnIntParameter(4, -'b' + 'c', returnInt(), test_assign_10, ('a')));
    int_array_test_assign[-+255 + int_array_test_assign[1] + 'b' * 2 - 196] = -'b' + 'c';
    
    char_test_assign = returnChar();
    char_array_test_assign[0] = returnCharParameter(4, 'a', returnChar(),  returnChar(), const_char_a);
    char_array_test_assign[1] = char_array_test_assign[0];
    char_array_test_assign[2] = 'x';
    
    printf(int_test_assign);
    printf(int_array_test_assign[0]);
    printf(int_array_test_assign[1]);
    printf(int_array_test_assign[2]);
    printf(char_test_assign);
    printf(char_array_test_assign[0]);
    printf(char_array_test_assign[1]);
    printf(char_array_test_assign[2]);

    int_global_var = -3;
    char_global_var = 'c';
}

void testInputOutput()
{
    int int_test_input;
    char char_test_input;
    int int_global_var;
    char char_global_var;
    scanf(int_test_input, char_test_input);
    printf(" !#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~");
    printf("int_test_input = ", int_test_input);
    printf("char_test_input = ",char_test_input);
    int_global_var = -4;
    char_global_var = 'd';
}

void testTrick()
{
    {;{};}
    {{{}}}
    ;;;;;;
}

int judge1(int a, int b, int c, int d)
{
    int ret;
    ret = 0;
    if(a < b)
        if(c >= d)
            ret = 1;
    return (ret);
}

int judge2(int a, int b, int c, int d)
{
    int ret;
    ret = 0;
    if(a < b)
        if(c <= d)
            ret = 1;
    return (ret);
}

void Qsort(int low, int high)
{
    int first, last, key;
    first = low;
    last = high;
    key = sort[first];
    if(low >= high)
        return;
    
    while(first < last)
    {
        while(judge1(first, last, sort[last], key) == 1)
            last = last - 1;
 
        sort[first] = sort[last];
 
        while(judge2(first, last, sort[first], key) == 1)
            first = first + 1;
         
        sort[last] = sort[first];    
    }
    sort[first] = key;
    Qsort(low, first-1);
    Qsort(first+1, high);
    return;
}

void testRecursion()
{
    int i;
    sort[0] = 5;
    sort[1] = 8;
    sort[2] = 3;
    sort[3] = 6;
    sort[4] = 4;
    sort[5] = 1;
    sort[6] = 2;
    sort[7] = 7;
    Qsort(0,7);
    i = 0;
    while(i < 8)
    {
        printf(sort[i]);
        i = i + 1;
    }
    int_global_var = -5;
    char_global_var = 'e';
}


void testCallFunction()
{
    int test_select;
    scanf(test_select);
    switch(test_select)
    {
    case 0:
        testIfWhile();
    case 1:
    {
        testSwitchCase(const_int_postive,const_char_a);
        testSwitchCase(const_int_negtive,'+');
        testSwitchCase(0,'_');
        testSwitchCase(2,'9');
        }
    case 2:
        testAssign();
    case 3:
        testInputOutput();
    case 4:
        testRecursion();
    }
    printf(int_global_var);
    printf(char_global_var);
}

void main()
{
    int_global_var = 0;
    char_global_var = '_';
    testCallFunction();
    testTrick();
} 
