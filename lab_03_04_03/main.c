#include "constants.h"
#include "errors.h"
#include "io.h"
#include "get_answer.h"


int main(void)
{
    int m[N][N];
    size_t m_n;;
    int rc;
    
    if ((rc = input_square_matrix(m, &m_n)) != OK)
    {
        print_error(rc);
        return rc;
    }
    
    bow_swap(m, m_n);
    print_matrix(m, m_n);
}
