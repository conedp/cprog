#include "constants.h"
#include "errors.h"
#include "io.h"
#include "get_answer.h"


int main(void)
{
    int m[N][M];
    size_t m_n, m_m;;
    int rc;
    
    if ((rc = input_matrix(m, &m_n, &m_m)) != OK)
    {
        print_error(rc);
        return rc;
    }
    
    insertion_sort(m, m_n, m_m);
    print_matrix(m, m_n, m_m);
}
