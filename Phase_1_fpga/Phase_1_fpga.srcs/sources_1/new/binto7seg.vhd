----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 15.05.2022 13:43:09
-- Design Name: 
-- Module Name: binto7seg - Behavioral
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

entity binto7seg is
  Port (Din: in std_logic_vector(3 downto 0);
        Dout:out std_logic_vector(6 downto 0));
end binto7seg;

architecture Behavioral of binto7seg is
Component fourtosixteendecoder
    Port (Qin:in std_logic_vector(3 downto 0);
          Qout:out std_logic_vector(15 downto 0));
end Component;
signal sig: std_logic_vector(15 downto 0);
signal A,B,C,D,E,F,G:std_logic;
begin
    decoder: fourtosixteendecoder port map(Qin=>Din,Qout=>sig);
    A <= sig(0) or sig(2) or sig(3) or sig(5) or sig(6) or sig(7) or sig(8) or sig(9);
    B <= sig(0) or sig(1) or sig(2) or sig(3) or sig(4) or sig(7) or sig(8) or sig(9);
    C <= sig(0) or sig(1) or sig(3) or sig(4) or sig(5) or sig(6) or sig(7) or sig(8) or sig(9);
    D <= sig(0) or sig(2) or sig(3) or sig(5) or sig(6) or sig(8);
    E <= sig(0) or sig(2) or sig(6) or sig(8);
    F <= sig(0) or sig(4) or sig(5) or sig(6) or sig(8) or sig(9);
    G <= sig(2) or sig(3) or sig(4) or sig(5) or sig(6) or sig(8) or sig(9);
    
    Dout <= G & F & E & D & C & B & A;
    
end Behavioral;
