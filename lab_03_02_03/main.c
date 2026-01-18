#include "constants.h"
#include "errors.h"
#include "io.h"
#include "get_answer.h"


int main(void)
{
    int m[N][M];
    size_t m_n, m_m;;
    int d;
    int rc;
    
    if ((rc = input_matrix(m, &m_n, &m_m)) != OK)
    {
        print_error(rc);
        return rc;
    }
    if ((rc = input_digit(&d)) != OK)
    {
        print_error(rc);
        return rc;
    }
    
    if ((rc = delete_columns_if_digit_in_num(m, m_n, &m_m, d)) != OK)
    {
        print_error(rc);
        return rc;
    }
    
    if (m_m == 0)
    {
        print_error(ERR_EMPTY_MATRIX);
        return ERR_EMPTY_MATRIX;
    }
    
    print_matrix(m, m_n, m_m);
    
    return OK;
}
