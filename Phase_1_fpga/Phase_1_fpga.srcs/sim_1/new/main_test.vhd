library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity main_test is
end main_test;

architecture Behavioral of main_test is

    Component main is
        Port (  a_num0_in: in std_logic_vector(1 downto 0);-- MCU signal and ready pins
                a_num0_out: out std_logic_vector(1 downto 0); -- FPGA data output pins
                a_num1_out: out std_logic_vector(1 downto 0);-- FPGA signal and ready pins
                b_num0: in std_logic_vector(3 downto 0); -- MCU data LSB pins
                b_num1: in std_logic_vector(3 downto 0);-- MCU data MSB pins

                CLK: in std_logic; -- Clock Signal
                S:out std_logic_vector(6 downto 0);-- Seven segment data signal
                an: out std_logic_vector(3 downto 0) --Seven segment anode signal
            );
    end Component;

    signal mcu_signal_signal : std_logic;
    signal mcu_ready_signal : std_logic;
    signal mcu_s_r : std_logic_vector(1 downto 0) := "00";
    signal data_a : std_logic_vector(3 downto 0);
    signal data_b : std_logic_vector(3 downto 0);
    signal mcu_data_signal : std_logic_vector(7 downto 0);

    signal fpga_signal_signal : std_logic;
    signal fpga_ready_signal : std_logic;
    signal fpga_s_r : std_logic_vector(1 downto 0);
    signal fpga_data : std_logic_vector(1 downto 0);
        
    signal clk_signal : std_logic;
begin
    mcu_s_r(0) <= mcu_signal_signal;
    mcu_s_r(1) <= mcu_ready_signal;
    data_a <= mcu_data_signal(3) & mcu_data_signal(2) & mcu_data_signal(1) & mcu_data_signal(0);
    data_b <= mcu_data_signal(7) & mcu_data_signal(6) & mcu_data_signal(5) & mcu_data_signal(4);
    fpga_signal_signal <= fpga_s_r(0);
    fpga_ready_signal <= fpga_s_r(1);

    UUT: main port map(
        a_num0_in => mcu_s_r,
        a_num0_out => fpga_data,
        a_num1_out => fpga_s_r,
        b_num0 => data_a,
        b_num1 => data_b,
        clk => clk_signal
    );

    process
    begin
    
    -- reset comm module
    mcu_ready_signal <= '0';
    wait for 5ps;
    mcu_ready_signal <= '1';
    wait for 5ps;

    --Write byte 1
    mcu_signal_signal <= '0';
    wait for 5ps;
    mcu_data_signal <= "00000001";
    mcu_signal_signal <= '1';
    wait for 5ps;

    mcu_signal_signal <= '0';
    wait for 5ps;
    mcu_data_signal <= "00000000";
    mcu_signal_signal <= '1';
    wait for 5ps;

    --Write byte 2
    mcu_signal_signal <= '0';
    wait for 5ps;
    mcu_data_signal <= "00000010";
    mcu_signal_signal <= '1';
    wait for 5ps;

    mcu_signal_signal <= '0';
    wait for 5ps;
    mcu_data_signal <= "00000000";
    mcu_signal_signal <= '1';
    wait for 5ps;

    --Write byte 3
    mcu_signal_signal <= '0';
    wait for 5ps;
    mcu_data_signal <= "00000011";
    mcu_signal_signal <= '1';
    wait for 5ps;

    mcu_signal_signal <= '0';
    wait for 5ps;
    mcu_data_signal <= "00000000";
    mcu_signal_signal <= '1';
    wait for 105ps;
    end process;

    process
    begin
        clk_signal <= '0';
        wait for 1ps;
        clk_signal <= '1';
        wait for 1ps;
    end process;
end Behavioral;