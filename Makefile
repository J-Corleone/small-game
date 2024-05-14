.PHONY: run

GAME :=

GAMES := snake snake+ pong

ifeq ($(filter $(GAME),$(GAMES)),)
    $(error we dont have this game. Available options: [$(GAMES)])
# 它前面不能是 tab
endif

run:
	@$(MAKE) -C $(GAME) run
