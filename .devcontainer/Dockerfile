# NOTE: 根据vscode的设计，本文件夹本不应该提交，因为开发环境可以根据开发者的喜好而随意变更。
# 但为引导大家使用devcontainer工具，现阶段本配置将基础的配置都设置好，开发者可以开箱即用。后面不合适再删除。
# 本配置默认用zsh，且将本地的zsh配置绑定到了容器中，所以请在本地安装ohmyzsh等zsh插件
FROM nexus3.sr:8060/sros/sros-build-env:main

RUN apt update && \
  apt install -y zsh && \ 
  chsh -s /bin/zsh   

ENV ROOT_DIR=/workspace/SubstrateDevelopment \
  ARCH=amd64 \
  PYTHONPATH=/workspace/sros-core/test:/workspace/sros-core/test/sr-modbus-sdk-py
