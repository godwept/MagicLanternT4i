/* AI-assisted experimental diagnostics for this fork. */
#include <module.h>
#include <dryos.h>
#include <menu.h>
#include <mem.h>

static MENU_UPDATE_FUNC(burst_malloc_display)
{
    MENU_SET_VALUE("%d KiB", GetFreeMemForMalloc() / 1024);
}

static MENU_UPDATE_FUNC(burst_alloc_display)
{
    MENU_SET_VALUE("%d KiB", GetFreeMemForAllocateMemory() / 1024);
}

static struct menu_entry burst_menu[] = {
    {
        .name = "Burst Performance",
        .select = menu_open_submenu,
        .help = "Read-only heap diagnostics; not RAW buffer capacity.",
        .children = (struct menu_entry[]) {
            {
                .name = "Malloc free",
                .update = burst_malloc_display,
                .icon_type = IT_ALWAYS_ON,
                .help = "Free bytes in the malloc pool, displayed in KiB.",
            },
            {
                .name = "AllocateMemory free",
                .update = burst_alloc_display,
                .icon_type = IT_ALWAYS_ON,
                .help = "Free bytes in the Canon allocation pool.",
            },
            MENU_EOL
        },
    },
};

static unsigned int burst_init(void)
{
    if (is_camera("650D", "1.0.4"))
        menu_add("Debug", burst_menu, COUNT(burst_menu));
    return 0;
}

static unsigned int burst_deinit(void)
{
    return 0;
}

MODULE_INFO_START()
    MODULE_INIT(burst_init)
    MODULE_DEINIT(burst_deinit)
MODULE_INFO_END()
