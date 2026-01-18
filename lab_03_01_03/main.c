#include "constants.h"
#include "errors.h"
#include "io.h"
#include "get_answer.h"


int main(void)
{
    int m[N][M];
    size_t m_n, m_m;
    int ans[N];
    int rc;
    
    if ((rc = input_matrix(m, &m_n, &m_m)) != OK)
    {
        print_error(rc);
        return rc;
    }
    
    make_is_mono_seq_array(m, m_n, m_m, ans);
    
    print_array(ans, m_n);
}
