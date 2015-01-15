common="-drive file=FreeBSD-RELEASE-10.1-64.qcow2 -smp 2,cores=1,threads=1,sockets=2 -m 2048"
net="-netdev tap,ifname=tap0,id=hostnet0,vhost=on,script=/etc/qemu-ifup,downscript=/etc/qemu-ifdown \
    -device virtio-net-pci,netdev=hostnet0,id=virtio-net-pci0"

net1="-netdev tap,ifname=tap0,id=hostnet0,vhost=on,script=/etc/qemu-ifup,downscript=/etc/qemu-ifdown"
#qemu-kvm  $common $net $kvm_append &
#qemu-kvm  $common $net&


kvm_append="-netdev tap,id=hostnet1,vhost=on,script=/etc/qemu-ifup-br0,downscript=/etc/qemu-ifdown-br0 \
	        -device virtio-net-pci,netdev=hostnet1,id=virtio-net-pci1,mac=00:00:00:00:00:01 \
	        -netdev tap,id=hostnet2,vhost=on,script=/etc/qemu-ifup-br0,downscript=/etc/qemu-ifdown-br0 \
	        -device virtio-net-pci,netdev=hostnet2,id=virtio-net-pci2,mac=00:00:00:00:00:02 \
			-serial pty -vnc :99 -qmp tcp:0:9999,server,nowait"
start_vm()
{
	local cmd="
	qemu-kvm -name freebsd \
	-hda FreeBSD-RELEASE-10.1-64.qcow2
	-netdev tap,id=hostnet0,vhost=on,script=/etc/qemu-ifup,downscript=downscript=/etc/qemu-ifdown \
	-device virtio-net-pci,netdev=hostnet0,id=virtio-net-pci0 \

	-smp 2,cores=1,threads=1,sockets=2  \
	-m 4096 >>./ips 2>&1 &"
	eval $cmd

}
start_vm
