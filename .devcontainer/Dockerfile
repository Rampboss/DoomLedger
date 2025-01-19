FROM ghcr.io/ledgerhq/ledger-app-builder/ledger-app-dev-tools:latest


ARG XAUTHORITY_CONTAINER=/tmp/x11_auth
ENV XAUTHORITY=${XAUTHORITY_CONTAINER}

RUN apk add --update docker openrc gdb gdb-multiarch
RUN rc-update add docker boot
