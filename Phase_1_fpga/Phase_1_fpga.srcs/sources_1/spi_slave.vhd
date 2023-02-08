----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 28.12.2022 21:26:18
-- Design Name: 
-- Module Name: comms_module - Behavioral
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
use ieee.std_logic_unsigned.all;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

-- Entity declaration for the SPI slave component
entity spi_slave is
    Port ( clk : in  STD_LOGIC;
           -- Clock input
           cs  : in  STD_LOGIC;
           -- Chip select input
           mosi: in  STD_LOGIC;
           -- Master out, slave in (MOSI) input
           miso: out STD_LOGIC;
           -- Master in, slave out (MISO) output
           sck : in  STD_LOGIC;
           -- Serial clock (SCK) input
           received: out std_logic_vector(7 downto 0);
           transmit: in std_logic_vector(7 downto 0)
         );
end spi_slave;

-- Architecture for the SPI slave component
architecture rtl of spi_slave is
    -- Signal to store the data to be transmitted
    signal tx_data: std_logic_vector(7 downto 0);
    -- Signal to store the received data
    signal rx_data: std_logic_vector(7 downto 0);
    -- Signal to keep track of the current bit being transmitted/received
    signal bit_cnt: integer range 0 to 7;
begin
    received <= rx_data;
    tx_data <= transmit;

    -- Process to transmit and receive data over the SPI bus
    process(clk)
    begin
        if (rising_edge(clk)) then
            if (cs = '0') then
                -- If chip select is active (low), transmit/receive data
                if (bit_cnt = 0) then
                    -- If this is the first bit, set the MISO output to the first bit of tx_data
                    miso <= tx_data(0);
                else
                    -- For all other bits, shift tx_data left by 1 bit and set the MISO output to the new first bit
                    tx_data <= '0' & tx_data(7 downto 1);
                    miso <= tx_data(0);
                end if;
                -- Increment bit counter
                bit_cnt <= bit_cnt + 1;
                -- If all bits have been transmitted/received, reset bit counter and shift rx_data right by 1 bit
                -- to make room for the new received bit
                if (bit_cnt = 8) then
                    bit_cnt <= 0;
                    rx_data <= rx_data(6 downto 0) & mosi;
                end if;
            else
                -- If chip select is inactive (high), reset bit counter and clear rx_data
                bit_cnt <= 0;
                rx_data <= (others => '0');
            end if;
        end if;
    end process;
end rtl;
