#include "constants.h"
#include "errors.h"
#include "io.h"
#include "get_answer.h"


int main(void)
{
    int m[N][N];
    size_t m_n;;
    int rc;
    
    if ((rc = input_len(&m_n)) != OK)
    {
        print_error(rc);
        return rc;
    }
    
    fill_spiral(m, m_n);
    
    print_matrix(m, m_n);
}
