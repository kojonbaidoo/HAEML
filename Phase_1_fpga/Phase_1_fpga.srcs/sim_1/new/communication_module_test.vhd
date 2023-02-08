----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 06.01.2023 23:04:57
-- Design Name: 
-- Module Name: comm_module_two_test - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity communication_module_test is
end communication_module_test;

architecture Behavioral of communication_module_test is

component communication_module is
    port(
        clk : in std_logic;
        mcu_data : in std_logic_vector(7 downto 0);
        mcu_signal : in std_logic;
        mcu_ready : in std_logic;

        fpga_signal : out std_logic;
        fpga_data : out std_logic_vector(1 downto 0);
        fpga_ready : out std_logic;

        input_1_data : out std_logic_vector(15 downto 0);
        input_2_data : out std_logic_vector(15 downto 0);
        input_3_data : out std_logic_vector(15 downto 0);

        nn_out_data : in std_logic_vector(1 downto 0);
        nn_done : in std_logic
    );
end component;

signal clk_sig : std_logic;
signal mcu_data_sig : std_logic_vector(7 downto 0);
signal mcu_signal_sig : std_logic;
signal mcu_ready_sig : std_logic;

signal fpga_signal_sig : std_logic;
signal fpga_data_sig : std_logic_vector(1 downto 0);
signal fpga_ready_sig : std_logic;

signal input_1_data_sig : std_logic_vector(15 downto 0);
signal input_2_data_sig : std_logic_vector(15 downto 0);
signal input_3_data_sig : std_logic_vector(15 downto 0);

signal nn_out_data_sig : std_logic_vector(1 downto 0);
signal nn_done_sig : std_logic;

begin
UUT: communication_module port map(  clk=>clk_sig,
                                mcu_data=>mcu_data_sig,
                                mcu_signal=>mcu_signal_sig,
                                mcu_ready=>mcu_ready_sig,

                                fpga_signal=>fpga_signal_sig,
                                fpga_data=>fpga_data_sig,
                                fpga_ready=>fpga_ready_sig,
                                
                                input_1_data=>input_1_data_sig,
                                input_2_data=>input_2_data_sig,
                                input_3_data=>input_3_data_sig,

                                nn_done=>nn_done_sig,
                                nn_out_data=>nn_out_data_sig
                                );
                                
process
begin

    -- reset comm module
    mcu_ready_sig <= '0';
    clk_sig <= '0';
    wait for 1ps;
    clk_sig <= '1';
    wait for 1ps;

    mcu_ready_sig <= '1';
    clk_sig <= '0';
    wait for 1ps;
    clk_sig <= '1';
    wait for 1ps;
    -- end of reset

    -- write byte 1
    mcu_signal_sig <= '1';
    clk_sig <= '0';
    wait for 1ps;
    clk_sig <= '1';
    wait for 1ps;

    mcu_signal_sig <= '0';
    clk_sig <= '0';
    wait for 1ps;
    clk_sig <= '1';
    wait for 1ps;
    
    mcu_data_sig <= "00000000";
    clk_sig <= '0';
    wait for 1ps;
    clk_sig <= '1';
    wait for 1ps;

    mcu_signal_sig <= '1';
    clk_sig <= '0';
    wait for 1ps;
    clk_sig <= '1';
    wait for 1ps;
    -- end of write byte

    -- write byte 2
    mcu_signal_sig <= '1';
    clk_sig <= '0';
    wait for 1ps;
    clk_sig <= '1';
    wait for 1ps;
    
    mcu_signal_sig <= '0';
    clk_sig <= '0';
    wait for 1ps;
    clk_sig <= '1';
    wait for 1ps;
    
    mcu_data_sig <= "00000101";
    clk_sig <= '0';
    wait for 1ps;
    clk_sig <= '1';
    wait for 1ps;

    mcu_signal_sig <= '1';
    clk_sig <= '0';
    wait for 1ps;
    clk_sig <= '1';
    wait for 1ps;
    -- end of write byte
    
    -- write byte 3
    mcu_signal_sig <= '1';
    clk_sig <= '0';
    wait for 1ps;
    clk_sig <= '1';
    wait for 1ps;

    mcu_signal_sig <= '0';
    clk_sig <= '0';
    wait for 1ps;
    clk_sig <= '1';
    wait for 1ps;
    
    mcu_data_sig <= "00000110";
    clk_sig <= '0';
    wait for 1ps;
    clk_sig <= '1';
    wait for 1ps;

    mcu_signal_sig <= '1';
    clk_sig <= '0';
    wait for 1ps;
    clk_sig <= '1';
    wait for 1ps;
    -- end of write byte

    -- write byte 4
    mcu_signal_sig <= '1';
    clk_sig <= '0';
    wait for 1ps;
    clk_sig <= '1';
    wait for 1ps;
    
    mcu_signal_sig <= '0';
    clk_sig <= '0';
    wait for 1ps;
    clk_sig <= '1';
    wait for 1ps;
    
    mcu_data_sig <= "00000000";
    clk_sig <= '0';
    wait for 1ps;
    clk_sig <= '1';
    wait for 1ps;

    mcu_signal_sig <= '1';
    clk_sig <= '0';
    wait for 1ps;
    clk_sig <= '1';
    wait for 1ps;
    -- end of write byte

    -- write byte 5
    mcu_signal_sig <= '1';
    clk_sig <= '0';
    wait for 1ps;
    clk_sig <= '1';
    wait for 1ps;

    mcu_signal_sig <= '0';
    clk_sig <= '0';
    wait for 1ps;
    clk_sig <= '1';
    wait for 1ps;
    
    mcu_data_sig <= "00000111";
    clk_sig <= '0';
    wait for 1ps;
    clk_sig <= '1';
    wait for 1ps;

    mcu_signal_sig <= '1';
    clk_sig <= '0';
    wait for 1ps;
    clk_sig <= '1';
    wait for 1ps;
    -- end of write byte

    -- write byte 6
    mcu_signal_sig <= '1';
    clk_sig <= '0';
    wait for 1ps;
    clk_sig <= '1';
    wait for 1ps;
    
    mcu_signal_sig <= '0';
    clk_sig <= '0';
    wait for 1ps;
    clk_sig <= '1';
    wait for 1ps;
    
    mcu_data_sig <= "00000000";
    clk_sig <= '0';
    wait for 1ps;
    clk_sig <= '1';
    wait for 1ps;

    mcu_signal_sig <= '1';
    clk_sig <= '0';
    wait for 1ps;
    clk_sig <= '1';
    wait for 1ps;
    -- end of write byte
end process;

end Behavioral;
