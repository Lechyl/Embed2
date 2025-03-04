/* SD/MMC Block device Library for MBED-OS
 * Copyright 2017 Roy Krikke
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef BD_SD_DISCO_F746NG_H
#define BD_SD_DISCO_F746NG_H

#include "mbed.h"
#include "BlockDevice.h"
#include "platform/PlatformMutex.h"
#include "stm32746g_discovery_sd.h"

#define BD_SD_DISCO_F746NG_MAJOR_VERSION 1
#define BD_SD_DISCO_F746NG_MINOR_VERSION 0
#define BD_SD_DISCO_F746NG_PATCH_VERSION 0

/**
 * BD_SD_DISCO_F746NG class.
 *  Block device class for creating a block device to access a SD/MMC card via SD/MMC interface on DISCO_F746NG
 *
 * Example:
 * @code
 * #include "mbed.h"
 * #include "SDBlockDeviceDISCOF746NG.h"
 *
 * DigitalOut led (LED1);
 *
 * // Instantiate the Block Device for sd card on DISCO-F746NG
 * SDBlockDeviceDISCOF746NG bd;
 * uint8_t block[512] = "Hello World!\n";
 *
 * int
 * main () {
 *   Serial pc(SERIAL_TX, SERIAL_RX);
 *   pc.baud (115200);
 *   printf("Start\n");
 *
 *   // Call the SDBlockDevice-DISCO-F746NG instance initialisation method.
 *   printf("sd card init...\n");
 *   if (0 != bd.init ()) {
 *     printf("Init failed \n");
 *     return -1;
 *   }
 *
 *   printf("sd size: %llu\n", bd.size ());
 *   printf("sd read size: %llu\n", bd.get_read_size ());
 *   printf("sd program size: %llu\n", bd.get_program_size ());
 *   printf("sd erase size: %llu\n\n", bd.get_erase_size ());
 *
 *   printf("sd erase...\n");
 *   if (0 != bd.erase (0, bd.get_erase_size ())) {
 *     printf ("Error Erasing block \n");
 *   }
 *
 *   // Write some the data block to the device
 *   printf("sd write: %s\n", block);
 *   if (0 == bd.program (block, 0, 512)) {
 *     // read the data block from the device
 *     printf ("sd read: ");
 *     if (0 == bd.read (block, 0, 512)) {
 *       // print the contents of the block
 *       printf ("%s", block);
 *     }
 *   }
 *
 *   // Call the BD_SD_DISCO_F746NG instance de-initialisation method.
 *   printf("sd card deinit...\n");
 *   if(0 != bd.deinit ()) {
 *     printf ("Deinit failed \n");
 *     return -1;
 *   }
 *
 *   // Blink led with 2 Hz
 *   while(true) {
 *     led = !led;
 *     wait (0.5);
 *   }
 * }
 * @endcode
 *
 */
class SDBlockDeviceDISCOF746NG : public BlockDevice
{
public:

    /** Lifetime of the memory block device
     *
     * Only a block size of 512 bytes is supported
     *
     */
    SDBlockDeviceDISCOF746NG();
    virtual ~SDBlockDeviceDISCOF746NG();

    /** Initialize a block device
     *
     *  @return         0 on success or a negative error code on failure
     */
    virtual int init() override;

    /** Deinitialize a block device
     *
     *  @return         0 on success or a negative error code on failure
     */
    virtual int deinit() override;

    /** Read blocks from a block device
     *
     *  @param buffer   Buffer to read blocks into
     *  @param addr     Address of block to begin reading from
     *  @param size     Size to read in bytes, must be a multiple of read block size
     *  @return         0 on success, negative error code on failure
     */
    virtual int read(void *buffer, bd_addr_t addr, bd_size_t size) override;

    /** Program blocks to a block device
     *
     *  The blocks must have been erased prior to being programmed
     *
     *  @param buffer   Buffer of data to write to blocks
     *  @param addr     Address of block to begin writing to
     *  @param size     Size to write in bytes, must be a multiple of program block size
     *  @return         0 on success, negative error code on failure
     */
    virtual int program(const void *buffer, bd_addr_t addr, bd_size_t size) override;

    /** Erase blocks on a block device
     *
     *  The state of an erased block is undefined until it has been programmed
     *
     *  @param addr     Address of block to begin erasing
     *  @param size     Size to erase in bytes, must be a multiple of erase block size
     *  @return         0 on success, negative error code on failure
     */
    virtual int erase(bd_addr_t addr, bd_size_t size) override;

    /** Get the size of a readable block
     *
     *  @return         Size of a readable block in bytes
     */
    virtual bd_size_t get_read_size() const override;

    /** Get the size of a programable block
     *
     *  @return         Size of a programable block in bytes
     */
    virtual bd_size_t get_program_size() const override;

    /** Get the size of a eraseable block
     *
     *  @return         Size of a eraseable block in bytes
     */
    virtual bd_size_t get_erase_size() const override;

    /** Get the total size of the underlying device
     *
     *  @return         Size of the underlying device in bytes
     */
    virtual bd_size_t size() const override;
    
    virtual const char * get_type() const override;
private:
    uint8_t _card_type;
    bd_size_t _read_size;
    bd_size_t _program_size;
    bd_size_t _erase_size;
    bd_size_t _block_size;
    bd_size_t _capacity_in_blocks;
    BSP_SD_CardInfo _current_card_info;
    uint8_t _sd_state;
    uint32_t _timeout;
    PlatformMutex _mutex;
    bool _is_initialized;

    virtual void
    lock () {
        _mutex.lock();
    }

    virtual void
    unlock() {
        _mutex.unlock ();
    }

};

#endif /* BD_SD_DISCO_F746NG_H */
