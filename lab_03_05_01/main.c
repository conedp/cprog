#include "constants.h"
#include "errors.h"
#include "io.h"
#include "get_answer.h"


int main(void)
{
    int m[N][M];
    size_t m_n, m_m;
    int rc;
    
    if ((rc = input_matrix(m, &m_n, &m_m)) != OK)
    {
        print_error(rc);
        return rc;
    }
    
    if ((rc = move_suitable_left_by_three(m, m_n, m_m)) != OK)
    {
        print_error(rc);
        return rc;
    }
    
    print_matrix(m, m_n, m_m);
}
