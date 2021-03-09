# Установка

```sh
git clone https://git.246060.ru/f1x1t/uncrustify ~/.config/uncrustify
```

# Настройка

Установить переменную окружения `UNCRUSTIFY_CONFIG`, например:

```sh
UNCRUSTIFY_CONFIG="${XDG_CONFIG_HOME}/uncrustify/default.cfg"
[ -e "${UNCRUSTIFY_CONFIG}" ] && export UNCRUSTIFY_CONFIG
```

