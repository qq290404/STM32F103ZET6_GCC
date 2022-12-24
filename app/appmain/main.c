#include "config.h"
#include "clog.h"

#include "task.h"

#ifdef _MAIN_DEBUG
#define main_debug_e	QPLOG_ERR
#define main_debug_w	QPLOG_WAR
#define main_debug_d	QPLOG_DEB
#else
#define main_debug_e(fmt, ...)
#define main_debug_w(fmt, ...)
#define main_debug_d(fmt, ...)
#endif

static inline void Print(void)
{                                                                                                        
	QPLOG_COLOR_R(COLOR_HIGHT_CYAN, "                                                                                                                ");
	QPLOG_COLOR_R(COLOR_HIGHT_CYAN, "   SSSSSSSSSSSSSSS TTTTTTTTTTTTTTTTTTTTTTTMMMMMMMM               MMMMMMMM 333333333333333    222222222222222    ");
	QPLOG_COLOR_R(COLOR_HIGHT_CYAN, " SS:::::::::::::::ST:::::::::::::::::::::TM:::::::M             M:::::::M3:::::::::::::::33 2:::::::::::::::22  ");
	QPLOG_COLOR_R(COLOR_HIGHT_CYAN, "S:::::SSSSSS::::::ST:::::::::::::::::::::TM::::::::M           M::::::::M3::::::33333::::::32::::::222222:::::2 ");
	QPLOG_COLOR_R(COLOR_HIGHT_CYAN, "S:::::S     SSSSSSST:::::TT:::::::TT:::::TM:::::::::M         M:::::::::M3333333     3:::::32222222     2:::::2 ");
	QPLOG_COLOR_R(COLOR_HIGHT_CYAN, "S:::::S            TTTTTT  T:::::T  TTTTTTM::::::::::M       M::::::::::M            3:::::3            2:::::2 ");
	QPLOG_COLOR_R(COLOR_HIGHT_CYAN, "S:::::S                    T:::::T        M:::::::::::M     M:::::::::::M            3:::::3            2:::::2 ");
	QPLOG_COLOR_R(COLOR_HIGHT_CYAN, " S::::SSSS                 T:::::T        M:::::::M::::M   M::::M:::::::M    33333333:::::3          2222::::2  ");
	QPLOG_COLOR_R(COLOR_HIGHT_CYAN, "  SS::::::SSSSS            T:::::T        M::::::M M::::M M::::M M::::::M    3:::::::::::3      22222::::::22   ");
	QPLOG_COLOR_R(COLOR_HIGHT_CYAN, "    SSS::::::::SS          T:::::T        M::::::M  M::::M::::M  M::::::M    33333333:::::3   22::::::::222     ");
	QPLOG_COLOR_R(COLOR_HIGHT_CYAN, "       SSSSSS::::S         T:::::T        M::::::M   M:::::::M   M::::::M            3:::::3 2:::::22222        ");
	QPLOG_COLOR_R(COLOR_HIGHT_CYAN, "            S:::::S        T:::::T        M::::::M    M:::::M    M::::::M            3:::::32:::::2             ");
	QPLOG_COLOR_R(COLOR_HIGHT_CYAN, "            S:::::S        T:::::T        M::::::M     MMMMM     M::::::M            3:::::32:::::2             ");
	QPLOG_COLOR_R(COLOR_HIGHT_CYAN, "SSSSSSS     S:::::S      TT:::::::TT      M::::::M               M::::::M3333333     3:::::32:::::2       222222");
	QPLOG_COLOR_R(COLOR_HIGHT_CYAN, "S::::::SSSSSS:::::S      T:::::::::T      M::::::M               M::::::M3::::::33333::::::32::::::2222222:::::2");
	QPLOG_COLOR_R(COLOR_HIGHT_CYAN, "S:::::::::::::::SS       T:::::::::T      M::::::M               M::::::M3:::::::::::::::33 2::::::::::::::::::2");
	QPLOG_COLOR_R(COLOR_HIGHT_CYAN, " SSSSSSSSSSSSSSS         TTTTTTTTTTT      MMMMMMMM               MMMMMMMM 333333333333333   22222222222222222222");
	QPLOG_COLOR_R(COLOR_HIGHT_CYAN, "                                                                                                                ");

    QPLOG_COLOR_R(COLOR_HIGHT_CYAN, "                                                                                                                            ");
    QPLOG_COLOR_R(COLOR_HIGHT_CYAN, "                                                                                                    iiii                    ");
    QPLOG_COLOR_R(COLOR_HIGHT_CYAN, "                                                                                                   i::::i                   ");
    QPLOG_COLOR_R(COLOR_HIGHT_CYAN, "                                                                                                    iiii                    ");
    QPLOG_COLOR_R(COLOR_HIGHT_CYAN, "                                                                                                                            ");
    QPLOG_COLOR_R(COLOR_HIGHT_CYAN, "  aaaaaaaaaaaaa  ppppp   ppppppppp   ppppp   ppppppppp      mmmmmmm    mmmmmmm     aaaaaaaaaaaaa   iiiiiiinnnn  nnnnnnnn    ");
    QPLOG_COLOR_R(COLOR_HIGHT_CYAN, "  a::::::::::::a p::::ppp:::::::::p  p::::ppp:::::::::p   mm:::::::m  m:::::::mm   a::::::::::::a  i:::::in:::nn::::::::nn  ");
    QPLOG_COLOR_R(COLOR_HIGHT_CYAN, "  aaaaaaaaa:::::ap:::::::::::::::::p p:::::::::::::::::p m::::::::::mm::::::::::m  aaaaaaaaa:::::a  i::::in::::::::::::::nn ");
    QPLOG_COLOR_R(COLOR_HIGHT_CYAN, "           a::::app::::::ppppp::::::ppp::::::ppppp::::::pm::::::::::::::::::::::m           a::::a  i::::inn:::::::::::::::n");
    QPLOG_COLOR_R(COLOR_HIGHT_CYAN, "    aaaaaaa:::::a p:::::p     p:::::p p:::::p     p:::::pm:::::mmm::::::mmm:::::m    aaaaaaa:::::a  i::::i  n:::::nnnn:::::n");
    QPLOG_COLOR_R(COLOR_HIGHT_CYAN, "  aa::::::::::::a p:::::p     p:::::p p:::::p     p:::::pm::::m   m::::m   m::::m  aa::::::::::::a  i::::i  n::::n    n::::n");
    QPLOG_COLOR_R(COLOR_HIGHT_CYAN, " a::::aaaa::::::a p:::::p     p:::::p p:::::p     p:::::pm::::m   m::::m   m::::m a::::aaaa::::::a  i::::i  n::::n    n::::n");
    QPLOG_COLOR_R(COLOR_HIGHT_CYAN, "a::::a    a:::::a p:::::p    p::::::p p:::::p    p::::::pm::::m   m::::m   m::::ma::::a    a:::::a  i::::i  n::::n    n::::n");
    QPLOG_COLOR_R(COLOR_HIGHT_CYAN, "a::::a    a:::::a p:::::ppppp:::::::p p:::::ppppp:::::::pm::::m   m::::m   m::::ma::::a    a:::::a i::::::i n::::n    n::::n");
    QPLOG_COLOR_R(COLOR_HIGHT_CYAN, "a:::::aaaa::::::a p::::::::::::::::p  p::::::::::::::::p m::::m   m::::m   m::::ma:::::aaaa::::::a i::::::i n::::n    n::::n");
    QPLOG_COLOR_R(COLOR_HIGHT_CYAN, " a::::::::::aa:::ap::::::::::::::pp   p::::::::::::::pp  m::::m   m::::m   m::::m a::::::::::aa:::ai::::::i n::::n    n::::n");
    QPLOG_COLOR_R(COLOR_HIGHT_CYAN, "  aaaaaaaaaa  aaaap::::::pppppppp     p::::::pppppppp    mmmmmm   mmmmmm   mmmmmm  aaaaaaaaaa  aaaaiiiiiiii nnnnnn    nnnnnn");
    QPLOG_COLOR_R(COLOR_HIGHT_CYAN, "                  p:::::p             p:::::p                                                                               ");
    QPLOG_COLOR_R(COLOR_HIGHT_CYAN, "                  p:::::p             p:::::p                                                                               ");
    QPLOG_COLOR_R(COLOR_HIGHT_CYAN, "                  p:::::::p           p:::::::p                                                                             ");
    QPLOG_COLOR_R(COLOR_HIGHT_CYAN, "                  p:::::::p           p:::::::p                                                                             ");
    QPLOG_COLOR_R(COLOR_HIGHT_CYAN, "                  p:::::::p           p:::::::p                                                                             ");
    QPLOG_COLOR_R(COLOR_HIGHT_CYAN, "                  ppppppppp           ppppppppp                                                                             ");
    QPLOG_COLOR_R(COLOR_HIGHT_CYAN, "                                                                                                                            ");

	RLS_DEBUG("+++app+++");
}

int main(int argc, char** argv)
{
	Print();
	UpdatePartitionInfo();

	OS_Bsp_Init();

	OSInit();

	TaskInit();

	OSStart();
}
