Feature: Indicadores luminosos com padrões de sinalização individualizados

    1. Os indicadores luminosos apresentam padrões de sinalização para indicar
    algum comportamento do sistema.

    2. Os padrões de sinalização incluem no mínimo:
    apagado, aceso, piscante e customizado.

    3. O padrão de sinalização de um indicador luminoso é independente dos demais.

    Background:
    Na sinalização de estado de um sistema é importante chamar a atenção do usuário
    para cenários que indiquem funcionamento normal, estados de configuração, alarme
    e erros.

    Deve levar em consideração que uma sinalização de um indicador que permanece apenas
    aceso, ou apagado, com algum tempo, se mistura com o ambiente e passa desapercebido
    para quem realiza o monitoramento ou inspeção visual.

    Além do padrão de sinalização, quando aplicável deve se incluir característica de
    cores de sinalização auditiva.


    Scenario: Troca de padrão de sinalização de um indicador luminoso
        Given Com o dispositivo em funcionamento,
        When Usuário necessita trocar o padrão de exibição de um indicador luminoso
        Then Usuário deve pressionar o botão que altera o padrão de sinalização do indicador luminoso corresponde
        And  Verificar a troca do padrão de sinalização do indicador luminoso


    Scenario: Inicialização dos indicadores luminosos
        Given Com o sistema em funcionamento
        When O usuário necessita reiniciar os padrões de sinalização (indicadores apagados)
        Then Deve pressionar botão de inicialização dos indicadores luminosos
        And Verificar que os indicadores ficam no padrão inicial (apagados)










