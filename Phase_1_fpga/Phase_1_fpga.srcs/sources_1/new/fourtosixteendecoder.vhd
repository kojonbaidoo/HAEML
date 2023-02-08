----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 15.05.2022 12:59:52
-- Design Name: 
-- Module Name: fourtosixteendecoder - Behavioral
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

entity fourtosixteendecoder is
    Port (Qin:in std_logic_vector(3 downto 0);
          Qout:out std_logic_vector(15 downto 0));
end fourtosixteendecoder;

architecture Behavioral of fourtosixteendecoder is

begin
    with Qin select
    Qout <= "0000000000000001" when "0000",
            "0000000000000010" when "0001",
            "0000000000000100" when "0010",
            "0000000000001000" when "0011",
            "0000000000010000" when "0100",
            "0000000000100000" when "0101",
            "0000000001000000" when "0110",
            "0000000010000000" when "0111",
            "0000000100000000" when "1000",
            "0000001000000000" when "1001",
            "0000010000000000" when "1010",
            "0000100000000000" when "1011",
            "0001000000000000" when "1100",
            "0010000000000000" when "1101",
            "0100000000000000" when "1110",
            "1000000000000000" when others;
end Behavioral;
