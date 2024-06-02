class CNetwork
{
public:
    CNetwork();
    ~CNetwork();

    BOOL    Create();
    void    FreeSessionList();

protected:
    int         m_field0_0x0;
    int         m_field8_0x20;
    int         m_field7_0x1c;
    int         m_pUnkC;
    void        m_pSessions;
    int         m_field3_0xc;
    void        m_field4_0x10;
    int         m_field5_0x14;
    int         m_field6_0x18;
    NetPlayer   m_players[4];
};