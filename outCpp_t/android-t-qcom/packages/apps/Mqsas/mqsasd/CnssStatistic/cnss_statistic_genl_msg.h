#define CNSS_STATISTIC_GENL_NAME "cnss_statistic"
#define CNSS_STATISTIC_GENL_VERSION 1
#define CNSS_STATISTIC_MULTICAST_GROUP_EVENT "events"

enum cnss_statistic_genl_commands
{
    CNSS_STATISTIC_GENL_CMD_UNSPEC,
    CNSS_STATISTIC_GENL_EVENT_WOW_WAKEUP,
    CNSS_STATISTIC_GENL_CMD_DEBUG,
    CNSS_STATISTIC_GENL_CMD_ENABLE,
    CNSS_STATISTIC_GENL_CMD_DISABLE,
    __CNSS_STATISTIC_GENL_CMD_MAX,
};
#define CNSS_STATISTIC_GENL_CMD_MAX (__CNSS_STATISTIC_GENL_CMD_MAX - 1)

enum
{
    CNSS_STATISTIC_GENL_ATTR_UNSPEC,
    CNSS_STATISTIC_GENL_ATTR_PROTO_SUBTYPE,
    CNSS_STATISTIC_GENL_ATTR_SRC_PORT,
    CNSS_STATISTIC_GENL_ATTR_DST_PORT,
    __CNSS_STATISTIC_GENL_ATTR_MAX,
};
#define CNSS_STATISTIC_GENL_ATTR_MAX (__CNSS_STATISTIC_GENL_ATTR_MAX - 1)
